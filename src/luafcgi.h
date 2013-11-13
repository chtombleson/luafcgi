#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#define LUA_LIB extern
#define PROJECT_TABLENAME "luafcgi" extern

extern char *host;
extern int  port;
int LUA_API luaopen_luafcgi (lua_State *L);
static int New(lua_State *L);
