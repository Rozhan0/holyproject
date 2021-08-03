add_library(server server.c)

IF(WIN32 OR WIN64)
    target_link_libraries(server ws2_32)
ENDIF()
