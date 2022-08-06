project(
  AggregateSignatures
  DESCRIPTION "An Experimental Study of Aggregate Signatures using the MCL pairings library"
  LANGUAGES CXX)

cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 20)

# Help cmake find our custom cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

add_subdirectory(src)
