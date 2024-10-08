cmake_minimum_required(VERSION 3.28)

project (
    Game_Engine
    VERSION 0.1
    DESCRIPTION "Game Engine project with CMake that will hoepfully make me pass my bachelor degree"
    LANGUAGES CXX C
    )

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    #standard cpp 14
    set(CMAKE_CXX_STANDARD 17)
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

include(FetchContent)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e 
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG 	v5.4.3
)
FetchContent_MakeAvailable(assimp)

add_subdirectory(GameEngine/src)
add_subdirectory(GameEngine/include)

if(MSVC)
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set(GLFW_CMAKE_STARTER_SRC "GameEngine/src/main.cpp")
set(GLAD_C_PATH "GameEngine/src/glad.c")

add_executable("${CMAKE_PROJECT_NAME}" ${GLFW_CMAKE_STARTER_SRC} ${GLAD_C_PATH})

#Adding external libraries to the project
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
    glm::glm
    GameEngineLib
    assimp
)
#Adding header files to the project
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/GameEngine/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/stb_image
    ${CMAKE_SOURCE_DIR}/external/glm
    ${CMAKE_SOURCE_DIR}/external/imgui
    ${CMAKE_SOURCE_DIR}/external/assimp
)

if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${CMAKE_PROJECT_NAME}" )
    endif()
endif()