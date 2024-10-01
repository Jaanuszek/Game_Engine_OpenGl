cmake_minimum_required(VERSION 3.28)

file(GLOB_RECURSE ENGINE_SRC
    "*.cpp"
)

add_library(GameEngineLib STATIC ${ENGINE_SRC})

target_link_libraries(GameEngineLib PRIVATE 
    OpenGL::GL  
    glfw 
    glm::glm
    assimp
)

target_include_directories(GameEngineLib PRIVATE
    ${CMAKE_SOURCE_DIR}/GameEngine/include
    ${CMAKE_SOURCE_DIR}/GameEngine/include/IO
    ${CMAKE_SOURCE_DIR}/GameEngine/include/objects
    ${CMAKE_SOURCE_DIR}/GameEngine/include/tests
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/stb_image
    ${CMAKE_SOURCE_DIR}/external/glm
    ${CMAKE_SOURCE_DIR}/external/imgui
    ${CMAKE_SOURCE_DIR}/external/assimp/include
)