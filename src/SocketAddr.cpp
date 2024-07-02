#include "SocketAddr.hpp"

#include <charconv>
#include <cstdint>
#include <format>
#include <ranges>
#include <system_error>
#include <vector>

namespace tcp {
    namespace {
        auto splitAddressIntoIpAndPort(std::string_view addr) noexcept //
            -> std::pair<std::string_view, std::string_view> {

            const auto portSep = addr.find_first_of(':');
            if(portSep != std::string_view::npos) {
                return { addr.substr(0, portSep), addr.substr(portSep + 1) };
            }
            return { addr, {} };
        }


        template <std::integral Int>
        auto parseInt(std::string_view str) noexcept -> std::pair<Int, std::errc> {
            std::pair<Int, std::errc> res = {};

            const auto& [last, ec] = std::from_chars(str.begin(), str.end(), res.first);
            res.second = (last != str.end()) ? std::errc::invalid_argument : ec;

            return res;
        }


        auto parsePort(std::string_view port) -> std::uint16_t {
            static constexpr std::uint16_t DefaultPort = 0;
            if(port.empty()) {
                return DefaultPort;
            }

            const auto& [value, ec] = parseInt<std::uint16_t>(port);
            switch(ec) {
                case std::errc::invalid_argument: {
                    throw std::runtime_error("invalid format for port number");
                }
                case std::errc::result_out_of_range: {
                    throw std::runtime_error("port number is out of range");
                }
                default: {
                    return value;
                }
            }
        }

        auto parseOctet(std::string_view oct) -> std::uint8_t {
            const auto& [value, ec] = parseInt<std::uint8_t>(oct);
            switch(ec) {
                case std::errc::invalid_argument: {
                    throw std::runtime_error("invalid format for IP address octets");
                }
                case std::errc::result_out_of_range: {
                    throw std::runtime_error("IP address octets are out of range");
                }
                default: {
                    return value;
                }
            }
        }


        auto parseAddress(std::string_view addr) -> SocketAddr {
            const auto& [ip, port] = splitAddressIntoIpAndPort(addr);

            std::vector<std::uint8_t> octets;
            for(const auto& oct : ip | std::views::split('.')) {
                octets.push_back(parseOctet({ oct.begin(), oct.end() }));
            }

            if(octets.size() == 4) {
                return {
                    .ip = { octets[0], octets[1], octets[2], octets[3] },
                    .port = parsePort(port)
                };
            }
            throw std::runtime_error("invalid IP address format");
        }
    }


    auto SocketAddr::fromString(std::string_view addr) -> SocketAddr {
        return parseAddress(addr);
    }

    auto SocketAddr::toString() const -> std::string {
        return std::format("{}.{}.{}.{}:{}", ip.a, ip.b, ip.c, ip.d, port);
    }
}
