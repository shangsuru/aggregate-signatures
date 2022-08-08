add_executable(benchmark benchmark.cpp bls.cpp)
target_link_libraries(benchmark PRIVATE mcl)