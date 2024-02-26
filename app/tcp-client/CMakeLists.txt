add_executable(tcp-client "main.cpp")

target_link_libraries(tcp-client
	PRIVATE tcp
)

target_compile_features(tcp-client PRIVATE cxx_std_20)
