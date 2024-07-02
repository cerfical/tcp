#include "ClientSocket.hpp"

#include "errors.hpp"
#include "util.hpp"

#include <sys/ioctl.h>
#include <sys/poll.h>

namespace tcp {
    namespace {
        void waitSocket(int sockfd) {
            pollfd fds = { .fd = sockfd, .events = POLLIN };
            sysCallCheck(poll(&fds, 1, -1));
        }

        auto socketAvailableData(int sockfd) -> std::size_t {
            int byteCount = {};
            sysCallCheck(ioctl(sockfd, FIONREAD, &byteCount));
            return byteCount;
        }
    }


    ClientSocket::ClientSocket(SocketAddr addr) {
        const auto sockaddr = toSockAddr(addr);
        sysCallCheck(connect(sock_.handle(), &sockaddr, sizeof(sockaddr)));
    }


    void ClientSocket::write(std::string_view data) {
        sysCallCheck(send(sock_.handle(), data.data(), data.size(), 0));
    }

    auto ClientSocket::read() -> std::string {
        const auto sockfd = sock_.handle();
        waitSocket(sockfd);
        const auto byteCount = socketAvailableData(sockfd);

        std::string buf(byteCount, '\0');
        sysCallCheck(recv(sockfd, buf.data(), buf.size(), 0));
        return buf;
    }
}
