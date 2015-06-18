cmake_minimum_required(VERSION 2.8)
project(luafcgi)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES
    src/deps/commander-1.3.2/src/commander.c
    src/deps/commander-1.3.2/src/commander.h
    src/luafcgi/functions/print.c
    src/luafcgi/functions/print.h
    src/luafcgi/functions/server.c
    src/luafcgi/functions/server.h
    src/luafcgi/functions/server_info.c
    src/luafcgi/functions/server_info.h
    src/luafcgi/luafcgi.c
    src/luafcgi/luafcgi.h
    src/main.c)

link_libraries(
    lua5.1
    fcgi
)
add_executable(luafcgi ${SOURCE_FILES})