cmake_minimum_required(VERSION 3.10)

project(Game_Engine_OpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Main project paths
set(SRC_DIR "${CMAKE_SOURCE_DIR}/GameEngine/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/GameEngine/include")
set(RES_DIR "${CMAKE_SOURCE_DIR}/GameEngine/res")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/GameEngine/Libraries")
#MAKE IT MORE FLEXIBLE!!!!!
set(glfw3_DIR "${CMAKE_SOURCE_DIR}/Libraries/include/GLFW/CMake") 

#Main include folder
include_directories(${INCLUDE_DIR})

#Exteral libs
include_directories(${LIB_DIR}/include) #???? Do I need this?
include_directories(${SRC_DIR}/vendor/glm)
include_directories(${SRC_DIR}/vendor/imgui)
include_directories(${SRC_DIR}/vendor/stb_image)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/GameEngine/Libraries/include/GLFW/CMake")

# Adding External libs
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(Game_Engine_OpenGL ${SOURCES} ${HEADERS})

target_link_libraries(Game_Engine_OpenGL OpenGL::GL glfw3)

if(MSVC)
    target_compile_options(Game_Engine_OpenGL PRIVATE /W4)
else()
    target_compile_options(Game_Engine_OpenGL PRIVATE -Wall -Wextra -pedantic)
endif()

target_compile_definitions(Game_Engine_OpenGL PRIVATE RES_DIR="${RES_DIR}")