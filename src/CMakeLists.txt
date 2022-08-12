add_executable(benchmark benchmark.cpp bls.cpp bgls.cpp)
target_link_libraries(benchmark PRIVATE mcl)