#include "Socket.hpp"

#include "errors.hpp"

#include <arpa/inet.h>

namespace tcp {
    Socket::Socket() {
        const auto sockfd = socket(AF_INET, SOCK_STREAM, 0);
        sysCallCheck(sockfd);

        sock_.reset(sockfd);
    }

    void Socket::SocketClose::operator()(pointer sock) const noexcept {
        sysCallNoFail(close(sock.value));
    }
}
