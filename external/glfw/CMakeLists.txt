cmake_minimum_required(VERSION 3.28)

add_subdirectory(glfw)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)