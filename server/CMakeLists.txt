add_library(server server.c)

IF(win32 OR win64)
    target_link_libraries(server ws2_32)
ENDIF()
