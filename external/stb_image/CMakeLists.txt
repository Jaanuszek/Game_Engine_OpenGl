cmake_minimum_required(VERSION 3.28)

add_library(stb_image STATIC stb_image.cpp)
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE stb_image)