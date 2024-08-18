cmake_minimum_required(VERSION 3.28)

project (
    Game_Engine
    VERSION 0.1
    DESCRIPTION "Game Engine project with CMake that will hoepfully make me pass my bachelor degree"
    LANGUAGES CXX
    )

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    #standard cpp 14
    set(CMAKE_CXX_STANDARD 14)
    # -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    #library to test CMake
    include(Ctest)
    #library for creating the documentation
    find_package(Doxygen)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

find_package (OpenGL REQUIRED)

add_subdirectory(external/glfw)
add_subdirectory(external/stb_image)
#add_subdirectory(external/glm)



include(FetchContent)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e 
)

FetchContent_MakeAvailable(glm)

add_subdirectory(GameEngine/src)
add_subdirectory(GameEngine/include)

#FindOpenGL Cmake component
#include_directories can be replaced with newest target_include_directories()
include_directories( ${OPENGL_INCLUDE_DIRS})

#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set(GLAD_GL "")

if(MSVC)
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set(GLFW_CMAKE_STARTER_SRC "GameEngine/src/main.cpp")
set(GLAD_C_PATH "GameEngine/src/glad.c")

add_executable("${CMAKE_PROJECT_NAME}" WIN32 ${GLFW_CMAKE_STARTER_SRC} ${GLAD_C_PATH})
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
    #stb_image
    #imgui
    glm::glm
    GameEngineLib
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/GameEngine/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/stb_image
    ${CMAKE_SOURCE_DIR}/external/glm
    ${CMAKE_SOURCE_DIR}/external/imgui
)

if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${CMAKE_PROJECT_NAME}" )
    endif()
endif()