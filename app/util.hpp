#pragma once

#include <tcp/SocketAddr.hpp>

#include <cctype>
#include <format>
#include <iostream>
#include <ranges>
#include <string_view>

inline auto error(std::string_view msg) -> int {
    const auto endDot = msg.find('.');
    const auto dotRemoved = (endDot != std::string_view::npos) ? msg.substr(0, endDot) : msg;

    const auto toLower = [](unsigned char ch) { return std::tolower(ch); };
    const auto lower = dotRemoved | std::views::transform(toLower);

    std::cerr << std::format("error: {}\n", std::string(lower.begin(), lower.end()));
    return -1;
}

inline auto parseAddress(int argc, const char** argv) -> tcp::SocketAddr {
    const auto args = std::span(argv, argc);
    if(args.size() != 2) {
        const auto msg = std::format("wrong usage: expected a single argument of the form <ip>[:<port>]");
        throw std::runtime_error(msg);
    }
    return tcp::SocketAddr::fromString(args[1]);
}
