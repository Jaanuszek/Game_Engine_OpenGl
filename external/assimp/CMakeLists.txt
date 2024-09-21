cmake_minimum_required(VERSION 3.28)
project(assimp)

add_library(assimp INTERFACE)
#target_sources(assimp PRIVATE include)
target_include_directories(assimp INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/")