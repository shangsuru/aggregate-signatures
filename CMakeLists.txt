cmake_minimum_required(VERSION 3.16)
project(
  AggregateSignatures
  VERSION 0.1
  DESCRIPTION "An Experimental Study of Aggregate Signatures using the MCL pairings library"
  LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

# Help cmake find our custom cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

add_subdirectory(src)

# Testing
include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    doctest
    PREFIX ${CMAKE_BINARY_DIR}/doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

# Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")
include_directories(${DOCTEST_INCLUDE_DIR})
add_subdirectory(tests)