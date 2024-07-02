#include "Socket.hpp"

#include "errors.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>

#include <format>

namespace tcp {
    namespace {
        auto toNetOrder(IpAddr addr) -> std::uint32_t {
            const auto addrstr = std::format("{}.{}.{}.{}", addr.a, addr.b, addr.c, addr.d);

            in_addr inAddr = {};
            sysCallCheck(inet_aton(addrstr.c_str(), &inAddr));

            return inAddr.s_addr;
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
}
