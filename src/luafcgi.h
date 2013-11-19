#include "fcgi_stdio.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#define LUA_LIB
#define PROJECT_TABLENAME "luafcgi"

const char* socket_path = NULL;
int socket = NULL;
int LUA_API luaopen_luafcgi (lua_State *L);
static int New(lua_State *L);
static int runApp(lua_State *L);
