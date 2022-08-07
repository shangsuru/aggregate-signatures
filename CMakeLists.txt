cmake_minimum_required(VERSION 3.16)
project(
  AggregateSignatures
  VERSION 0.1
  DESCRIPTION "An Experimental Study of Aggregate Signatures using the MCL pairings library"
  LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

# Help cmake find our custom cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(FetchContent)

# MCL Pairing Library
FetchContent_Declare(
  MCL
  GIT_REPOSITORY "https://github.com/herumi/mcl"
  GIT_TAG "v1.68"
)
FetchContent_MakeAvailable(MCL)
# Exclude from clang-tidy analysis
set_target_properties(mcl PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:mcl,INTERFACE_INCLUDE_DIRECTORIES>)

add_subdirectory(src)

# Testing
option(ENABLE_DOCTESTS "Include tests in the library." ON)
include(DocTest)