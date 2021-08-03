cmake_minimum_required(VERSION 3.1)

project(holyproject C)

add_subdirectory(database)
add_subdirectory(parse)
add_subdirectory(server)

add_executable(Main main.c)

target_link_libraries(Main PUBLIC database)
target_link_libraries(Main PUBLIC parse)
target_link_libraries(Main PUBLIC server)

target_include_directories( Main PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/database"
                            "${PROJECT_SOURCE_DIR}/parse"
                            "${PROJECT_SOURCE_DIR}/server"
                            )
