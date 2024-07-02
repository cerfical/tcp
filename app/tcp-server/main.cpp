#include "../util.hpp"

#include <tcp/ServerSocket.hpp>

#include <csignal>
#include <exception>
#include <format>
#include <iostream>

auto main(int argc, const char** argv) noexcept -> int {
    try {
        const auto servAddr = parseAddress(argc, argv);
        std::cout << std::format("starting a server on {}...\n", servAddr.toString());

        auto servSock = tcp::ServerSocket(servAddr);

        std::cout << "server started successfully\n";
        std::cout << "use tcp-client to send messages, Ctrl+C to exit\n";
        std::cout << '\n';

        while(true) {
            auto clientSock = servSock.accept();
            while(true) {
                const auto msg = clientSock.read();
                if(msg.empty()) {
                    break;
                }
                std::cout << std::format("> {}\n", msg);
            }
        }
    } catch(const std::exception& e) {
        return error(e.what());
    }
}
