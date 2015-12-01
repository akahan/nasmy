cmake_minimum_required(VERSION 3.2.0)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "-ferror-limit=100 -fspell-checking -Wunused-parameter -Wunreachable-code -Wall -std=c++11")

project(Nasmy)

add_subdirectory(src)
