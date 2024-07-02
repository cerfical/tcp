#pragma once

#include <cstdint>

namespace tcp {

    struct IpAddr {
        std::uint8_t a = {};
        std::uint8_t b = {};
        std::uint8_t c = {};
        std::uint8_t d = {};
    };

}
