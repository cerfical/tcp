#pragma once

#include "IpAddr.hpp"
#include "Socket.hpp"

#include <cstdint>

namespace tcp {

    class ClientSocket {
    public:

        ClientSocket(const ClientSocket&) = delete;
        auto operator=(const ClientSocket&) -> ClientSocket& = delete;

        ClientSocket(ClientSocket&&) noexcept = default;
        auto operator=(ClientSocket&&) noexcept -> ClientSocket& = default;

        ~ClientSocket() = default;


        ClientSocket() noexcept
            : sock_(0) {}

        ClientSocket(IpAddr addr, std::uint16_t port);


        void write(std::string_view data);

        [[nodiscard]]
        auto read() -> std::string;


    private:
        Socket sock_;
    };

}
