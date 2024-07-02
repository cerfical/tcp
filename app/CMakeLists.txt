add_executable(tcp-client "tcp-client/main.cpp")

target_compile_features(tcp-client PRIVATE cxx_std_20)
target_link_libraries(tcp-client PRIVATE tcp)


add_executable(tcp-server "tcp-server/main.cpp")

target_compile_features(tcp-server PRIVATE cxx_std_20)
target_link_libraries(tcp-server PRIVATE tcp)
