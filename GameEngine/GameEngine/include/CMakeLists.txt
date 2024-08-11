target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(IO)
add_subdirectory(objects)
add_subdirectory(tests)