#include <fcgiapp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>

#ifndef LUAFCGI_H
#define LUAFCGI_H
// Global vars
FCGX_Request request;
lua_State *Lua;
#endif
