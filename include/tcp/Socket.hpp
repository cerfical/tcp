#pragma once

#include "IpAddr.hpp"

#include <cstdint>
#include <memory>

namespace tcp {

    class Socket {
    public:

        Socket(const Socket&) = delete;
        auto operator=(const Socket&) -> Socket& = delete;

        Socket(Socket&&) noexcept = default;
        auto operator=(Socket&&) noexcept -> Socket& = default;

        ~Socket() = default;


        Socket() noexcept = default;

        Socket(IpAddr addr, std::uint16_t port);


    private:
        struct SocketHandle {

            friend auto operator==(SocketHandle, SocketHandle) noexcept -> bool = default;


            SocketHandle() noexcept = default;

            SocketHandle(std::nullptr_t) noexcept
                : SocketHandle(0) {}

            SocketHandle(int value) noexcept
                : value(value) {}


            explicit operator bool() const noexcept {
                return value != 0;
            }


            int value = {};
        };

        struct SocketClose {
            using pointer = SocketHandle;

            void operator()(pointer sock) const noexcept;
        };

        std::unique_ptr<SocketHandle, SocketClose> sock_;
    };

}
