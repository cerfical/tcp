add_executable(tcp-server "main.cpp")

target_link_libraries(tcp-server
    PRIVATE tcp
)

target_compile_features(tcp-server PRIVATE cxx_std_20)
