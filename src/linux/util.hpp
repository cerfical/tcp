#pragma once

#include "SocketAddr.hpp"
#include "errors.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>

#include <format>

namespace tcp {
    inline auto toNboBinary(IpAddr addr) -> std::uint32_t {
        const auto addrstr = std::format("{}.{}.{}.{}", addr.a, addr.b, addr.c, addr.d);

        in_addr inAddr = {};
        sysCallCheck(inet_aton(addrstr.c_str(), &inAddr));

        return inAddr.s_addr;
    }

    inline auto toSockAddr(SocketAddr addr) -> sockaddr {
        const auto sock = sockaddr_in {
            .sin_family = AF_INET,
            .sin_port = htons(addr.port),
            .sin_addr = { toNboBinary(addr.ip) },
        };
        return *reinterpret_cast<const sockaddr*>(&sock);
    }
}
