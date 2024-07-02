#include "Socket.hpp"

#include "errors.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/select.h>

#include <poll.h>

#include <format>

namespace tcp {
    namespace {
        auto toNetOrder(IpAddr addr) -> std::uint32_t {
            const auto addrstr = std::format("{}.{}.{}.{}", addr.a, addr.b, addr.c, addr.d);

            in_addr inAddr = {};
            sysCallCheck(inet_aton(addrstr.c_str(), &inAddr));

            return inAddr.s_addr;
        }


        void waitSocket(int sockfd) {
            pollfd pollfd = { .fd = sockfd, .events = POLLIN };
            sysCallCheck(poll(&pollfd, 1, -1));
        }


        auto socketAvailableData(int sockfd) -> std::size_t {
            int byteCount = {};
            sysCallCheck(ioctl(sockfd, FIONREAD, &byteCount));
            return byteCount;
        }
    }


    Socket::Socket(IpAddr addr, std::uint16_t port) {
        const auto sockfd = socket(AF_INET, SOCK_STREAM, 0);
        sysCallCheck(sockfd);

        sock_.reset(sockfd);

        const auto sockin = sockaddr_in {
            .sin_family = AF_INET,
            .sin_port = htons(port),
            .sin_addr = { toNetOrder(addr) },
        };
        sysCallCheck(connect(sockfd, reinterpret_cast<const sockaddr*>(&sockin), sizeof(sockin)));
    }

    void Socket::SocketClose::operator()(pointer sock) const noexcept {
        sysCallNoFail(close(sock.value));
    }


    void Socket::write(std::string_view data) {
        sysCallCheck(send(sock_.get().value, data.data(), data.size(), 0));
    }

    auto Socket::read() -> std::string {
        const auto sockfd = sock_.get().value;
        waitSocket(sockfd);
        const auto byteCount = socketAvailableData(sockfd);

        auto buf = std::string(byteCount, '\0');
        sysCallCheck(recv(sockfd, buf.data(), buf.size(), 0));
        return buf;
    }
}
