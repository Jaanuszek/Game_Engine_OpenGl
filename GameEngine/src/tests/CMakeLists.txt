# Find test source files
file(GLOB TESTS_SOURCE_FILES "${CMAKE_SOURCE_DIR}/GameEngine/src/tests/*.cpp")

set(GLAD_PATH_FOR_TEST "${CMAKE_SOURCE_DIR}/GameEngine/src/glad.c")

# Create the test executable
add_executable(GameEngineTests ${TESTS_SOURCE_FILES} ${GLAD_PATH_FOR_TEST})

# Link GTest and the Game Engine library
target_link_libraries(GameEngineTests PRIVATE
    OpenGL::GL  
    glfw 
    glm::glm
    assimp
    gtest
    gtest_main
    gmock
    gmock_main
    GameEngineLib
)

# Set up include directories for Game Engine headers 
target_include_directories(GameEngineTests PRIVATE
    ${CMAKE_SOURCE_DIR}/GameEngine/include
    ${CMAKE_SOURCE_DIR}/GameEngine/include/factories
    ${CMAKE_SOURCE_DIR}/GameEngine/include/IO
    ${CMAKE_SOURCE_DIR}/GameEngine/include/objects
    ${CMAKE_SOURCE_DIR}/GameEngine/include/tests
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/stb_image
    ${CMAKE_SOURCE_DIR}/external/glm
    ${CMAKE_SOURCE_DIR}/external/imgui
)

# Enable testing
enable_testing()
add_test(NAME GameEngineTests COMMAND GameEngineTests)