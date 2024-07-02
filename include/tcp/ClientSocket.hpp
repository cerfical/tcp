#pragma once

#include "Socket.hpp"
#include "SocketAddr.hpp"

namespace tcp {

    class ClientSocket {
    public:

        ClientSocket(const ClientSocket&) = delete;
        auto operator=(const ClientSocket&) -> ClientSocket& = delete;

        ClientSocket(ClientSocket&&) noexcept = default;
        auto operator=(ClientSocket&&) noexcept -> ClientSocket& = default;

        ~ClientSocket() = default;


        explicit ClientSocket(int handle = 0) noexcept
            : sock_(handle) {}

        explicit ClientSocket(SocketAddr addr);


        void write(std::string_view data);

        [[nodiscard]]
        auto read() -> std::string;


    private:
        Socket sock_;
    };

}
