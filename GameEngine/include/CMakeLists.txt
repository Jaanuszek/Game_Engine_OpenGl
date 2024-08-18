cmake_minimum_required(VERSION 3.28)

add_library(GameEngineHeaders INTERFACE)

target_include_directories(GameEngineHeaders INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GameEngineLib PRIVATE GameEngineHeaders)