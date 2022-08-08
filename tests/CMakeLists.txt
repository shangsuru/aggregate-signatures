add_executable(bls-t bls-t.cpp ${CMAKE_SOURCE_DIR}/src/bls.cpp)
target_link_libraries(bls-t mcl)
target_include_directories(bls-t SYSTEM PUBLIC ${DOCTEST_INCLUDE_DIR})