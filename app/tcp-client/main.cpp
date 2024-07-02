#include "../util.hpp"

#include <tcp/ClientSocket.hpp>

#include <exception>
#include <format>
#include <iostream>

auto main(int argc, const char** argv) noexcept -> int {
    try {
        const auto servAddr = parseAddress(argc, argv);
        std::cout << std::format("connecting to a server {}...\n", servAddr.toString());

        auto clientSock = tcp::ClientSocket(servAddr);

        std::cout << "connection with the server was successfully established\n";
        std::cout << "type messages on standard input to send, Ctrl+C to exit\n";
        std::cout << '\n';

        while(true) {
            std::cout << "> ";

            std::string msg;
            std::getline(std::cin, msg);
            clientSock.write(msg);
        }
    } catch(const std::exception& e) {
        return error(e.what());
    }
}
