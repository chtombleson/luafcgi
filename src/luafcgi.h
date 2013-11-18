#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#define LUA_LIB
#define PROJECT_TABLENAME "luafcgi"

const char* host;
int  port;
int LUA_API luaopen_luafcgi (lua_State *L);
static int New(lua_State *L);
static int getHost(lua_State *L);
static int getPort(lua_State *L);
