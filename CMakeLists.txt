cmake_minimum_required(VERSION 3.23)


if(NOT LINUX)
	message(FATAL_ERROR "Only Linux platforms are currently supported")
endif()


project(tcp LANGUAGES CXX DESCRIPTION "Trivial console app for TCP client/server communication")


add_library(tcp INTERFACE)

target_sources(tcp
	INTERFACE FILE_SET HEADERS BASE_DIRS "include" FILES
		"include/tcp/tcp.hpp"
)

target_compile_features(tcp INTERFACE cxx_std_20)


add_subdirectory(app/tcp-client)
add_subdirectory(app/tcp-server)
