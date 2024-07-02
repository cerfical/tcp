#pragma once

#include "ClientSocket.hpp"
#include "Socket.hpp"
#include "SocketAddr.hpp"

namespace tcp {

    class ServerSocket {
    public:

        ServerSocket(const ServerSocket&) = delete;
        auto operator=(const ServerSocket&) -> ServerSocket& = delete;

        ServerSocket(ServerSocket&&) noexcept = default;
        auto operator=(ServerSocket&&) noexcept -> ServerSocket& = default;

        ~ServerSocket() = default;


        ServerSocket() noexcept
            : sock_(0) {}

        explicit ServerSocket(SocketAddr addr);


        [[nodiscard]]
        auto accept() -> ClientSocket;


    private:
        Socket sock_;
    };

}
