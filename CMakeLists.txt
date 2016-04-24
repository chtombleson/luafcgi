cmake_minimum_required(VERSION 2.8)
project(luafcgi)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES
    src/functions/print.c
    src/functions/server.c
    src/functions/server_info.c
    src/luafcgi.c
)

link_libraries(
    lua5.2
    fcgi
)

add_executable(luafcgi ${SOURCE_FILES})

