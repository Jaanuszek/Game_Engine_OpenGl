cmake_minimum_required(VERSION 3.28)
project(imgui)

file(GLOB_RECURSE IMGUI_SRC
    "*.h"
    "*.cpp"
)

add_library(imgui STATIC ${IMGUI_SRC})
target_link_libraries(imgui PRIVATE glfw)
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
