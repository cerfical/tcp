cmake_minimum_required(VERSION 3.23)


if(NOT LINUX)
    message(FATAL_ERROR "Only Linux platforms are currently supported")
endif()


project(tcp LANGUAGES CXX DESCRIPTION "Trivial console app for TCP client/server communication")

add_library(tcp)


target_compile_features(tcp PUBLIC cxx_std_20)

target_include_directories(tcp
    PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    PRIVATE "include/tcp"
)

target_sources(tcp
    INTERFACE FILE_SET HEADERS BASE_DIRS "include" FILES
        "include/tcp/Socket.hpp"
        "include/tcp/ClientSocket.hpp"
        "include/tcp/ServerSocket.hpp"
        "include/tcp/IpAddr.hpp"
        "include/tcp/SocketAddr.hpp"

    PRIVATE
        "src/linux/Socket.cpp"
        "src/linux/ClientSocket.cpp"
        "src/linux/ServerSocket.cpp"
        "src/linux/errors.hpp"
        "src/linux/util.hpp"

        "src/SocketAddr.cpp"
)


add_subdirectory(app)


# Generate .gitignore file to take care of the build directory automatically
file(WRITE "${CMAKE_BINARY_DIR}/.gitignore" [[
*
]])
