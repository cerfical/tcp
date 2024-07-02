#pragma once

#include "ClientSocket.hpp"
#include "IpAddr.hpp"
#include "Socket.hpp"

#include <cstdint>

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

        ServerSocket(IpAddr addr, std::uint16_t port);


        [[nodiscard]]
        auto accept() -> ClientSocket;


    private:
        Socket sock_;
    };

}
