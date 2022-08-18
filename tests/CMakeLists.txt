add_executable(bls-t bls-t.cpp ${CMAKE_SOURCE_DIR}/src/bls.cpp)
target_link_libraries(bls-t mcl)
target_include_directories(bls-t SYSTEM PUBLIC ${DOCTEST_INCLUDE_DIR})

add_executable(bgls-t bgls-t.cpp ${CMAKE_SOURCE_DIR}/src/bgls.cpp ${CMAKE_SOURCE_DIR}/src/bls.cpp)
target_link_libraries(bgls-t mcl)
target_include_directories(bgls-t SYSTEM PUBLIC ${DOCTEST_INCLUDE_DIR})

add_executable(fischlin-t fischlin-t.cpp ${CMAKE_SOURCE_DIR}/src/fischlin.cpp ${CMAKE_SOURCE_DIR}/src/bls.cpp)
target_link_libraries(fischlin-t mcl)
target_include_directories(fischlin-t SYSTEM PUBLIC ${DOCTEST_INCLUDE_DIR})