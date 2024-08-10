cmake_minimum_required(VERSION 3.28)

project (Game_Engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (OpenGL REQUIRED)

#FindOpenGL Cmake component
#include_directories can be replaced with newest target_include_directories()
include_directories( ${OPENGL_INCLUDE_DIRS})

#set(SRC_DIR "${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/src")
#set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/include")
#set(RES_DIR "${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/res")
#set(LIB_DIR "${CMAKE_SOURCE_DIR}/GameEngine/Libraries")

include_directories(GameEngine/GameEngine/include)
include_directories(GameEngine/GameEngine/res)
include_directories(GameEngine/GameEngine/src)
include_directories(GameEngine/Libraries/glad) #could potentially makes a problem
include_directories(GameEngine/Libraries/KHR)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLAD_GL "")

add_subdirectory(GameEngine/Libraries/glfw)
add_subdirectory(GameEngine/GameEngine/src/vendor/glm)

option (GLFW_CMAKE_USE_GLFW_GLAD "Use Glad from GLFW" ON)

#if we want to use glad that is included into glfw
if(GLFW_CMAKE_USE_GLFW_GLAD)
    include_directories("${GLFW_SOURCE_DIR}/deps")
    set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h")
endif()

if(MSVC)
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set(GLFW_CMAKE_STARTER_SRC "GameEngine/GameEngine/src/main.cpp")

file(GLOB_RECURSE VENDOR_SOURCES
    "GameEngine/GameEngine/src/vendor/*.cpp"
    "GameEngine/GameEngine/src/vendor/*.c"
    "GameEngine/GameEngine/src/vendor/*.inl"
)
file(GLOB_RECURSE VENDOR_HEADERS
    "GameEngine/GameEngine/src/vendor/*.h"
    "GameEngine/GameEngine/src/vendor/*.hpp"
)

file(GLOB_RECURSE SOURCES
    "GameEngine/GameEngine/src/*.cpp"
    "GameEngine/GameEngine/src/*.c"
)

file(GLOB_RECURSE HEADERS
    "GameEngine/GameEngine/include/*.h"
    "GameEngine/GameEngine/include/*.hpp"
)



foreach(HEADER ${HEADERS})
    get_filename_component(HEADER_PATH "${HEADER}" PATH)
    file(RELATIVE_PATH HEADER_GROUP "${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/include" "${HEADER_PATH}")
    string(REPLACE "/" "\\" HEADER_GROUP "${HEADER_GROUP}")
    source_group("Header Files\\${HEADER_GROUP}" FILES "${HEADER}")
endforeach()

foreach(SOURCE ${SOURCES})
    get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
    file(RELATIVE_PATH SOURCE_GROUP "${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/src" "${SOURCE_PATH}")
    string(REPLACE "/" "\\" SOURCE_GROUP "${SOURCE_GROUP}")
    source_group("Source Files\\${SOURCE_GROUP}" FILES "${SOURCE}")
endforeach()

source_group("Vendor Libraries\\Source Files" FILES ${VENDOR_SOURCES})
source_group("Vendor Libraries\\Header Files" FILES ${VENDOR_HEADERS})

#add_library(vendor_libs STATIC ${VENDOR_SOURCES} ${VENDOR_HEADERS})

add_executable("${CMAKE_PROJECT_NAME}" WIN32 ${GLFW_CMAKE_STARTER_SRC} ${GLAD_GL} ${SOURCES} ${HEADERS})
target_link_libraries("${CMAKE_PROJECT_NAME}" ${OPENGL_LIBRARIES} glfw glm)
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE GameEngine/Libraries/glad GameEngine/Libraries/KHR)


if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${CMAKE_PROJECT_NAME}" )
    endif()
endif()