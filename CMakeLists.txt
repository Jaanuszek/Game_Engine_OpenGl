cmake_minimum_required(VERSION 3.28)

project (Game_Engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (OpenGL REQUIRED)

#FindOpenGL Cmake component
#include_directories can be replaced with newest target_include_directories()
include_directories( ${OPENGL_INCLUDE_DIRS})

#include_directories(GameEngine/GameEngine/include)
#include_directories(GameEngine/GameEngine/res)
#include_directories(GameEngine/GameEngine/src)
#include_directories(GameEngine/Libraries/glad) #could potentially makes a problem
#include_directories(GameEngine/Libraries/KHR)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLAD_GL "")

add_subdirectory(GameEngine/Libraries/glfw)
#add_subdirectory(GameEngine/GameEngine/src/vendor/glm)
#add_subdirectory(GameEngine/Libraries/include)

#option (GLFW_CMAKE_USE_GLFW_GLAD "Use Glad from GLFW" ON)

#if we want to use glad that is included into glfw
#if(GLFW_CMAKE_USE_GLFW_GLAD)
#    include_directories("${GLFW_SOURCE_DIR}/deps")
#    set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h")
#endif()

if(MSVC)
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set(GLFW_CMAKE_STARTER_SRC "GameEngine/GameEngine/src/main.cpp")

#add_executable("${CMAKE_PROJECT_NAME}" WIN32 ${GLFW_CMAKE_STARTER_SRC} ${GLAD_GL} ${SOURCES} ${HEADERS})
add_executable("${CMAKE_PROJECT_NAME}" WIN32 ${GLFW_CMAKE_STARTER_SRC} ${SOURCES} ${HEADERS})
target_link_libraries("${CMAKE_PROJECT_NAME}" ${OPENGL_LIBRARIES} glfw glm)
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE 
    GameEngine/Libraries/include
    GameEngine/Libraries/include/GLFW 
    GameEngine/Libraries/include/KHR
)
add_subdirectory(GameEngine/GameEngine/include)


if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${CMAKE_PROJECT_NAME}" )
    endif()
endif()