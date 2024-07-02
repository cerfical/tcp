#pragma once

#include <concepts>
#include <system_error>

namespace tcp {
    inline void sysCallCheck(std::signed_integral auto res) {
        if(res < 0) {
            throw std::system_error(errno, std::system_category());
        }
    }

    inline void sysCallNoFail(std::signed_integral auto res) noexcept {
        try {
            sysCallCheck(res);
        } catch(...) {
            std::terminate();
        }
    }
}
