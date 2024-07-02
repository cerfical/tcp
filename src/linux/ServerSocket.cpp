#include "ServerSocket.hpp"

#include "ClientSocket.hpp"
#include "errors.hpp"
#include "util.hpp"

#include <sys/socket.h>

namespace tcp {
    ServerSocket::ServerSocket(SocketAddr addr) {
        const auto sockaddr = toSockAddr(addr);
        sysCallCheck(bind(sock_.handle(), &sockaddr, sizeof(sockaddr)));
        sysCallCheck(listen(sock_.handle(), 0));
    }

    auto ServerSocket::accept() -> ClientSocket {
        const auto sockfd = ::accept(sock_.handle(), nullptr, nullptr);
        sysCallCheck(sockfd);

        return ClientSocket(sockfd);
    }
}
