#pragma once

#include "IpAddr.hpp"

#include <cstdint>
#include <string_view>

namespace tcp {

    struct SocketAddr {

        [[nodiscard]]
        static auto fromString(std::string_view addr) -> SocketAddr;

        [[nodiscard]]
        auto toString() const -> std::string;


        IpAddr ip;
        std::uint16_t port = {};
    };

}
