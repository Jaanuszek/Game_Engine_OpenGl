target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB IO_HEADERS_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

source_group("Header Files\\IO" FILES ${IO_HEADER_FILES})

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${IO_HEADER_FILES})