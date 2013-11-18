#include "luafcgi.h"

static int New(lua_State *L) {
    int arg_n = lua_gettop(L);

    if (arg_n > 2) {
        lua_pushstring(L, "luafcgi.New take 2 arguments");
        lua_error(L);
        return 0;
    }

    if (!lua_isstring(L, 1)) {
        lua_pushstring(L, "luafcgi.New expects a string as the first argument");
        lua_error(L);
        return 0;
    }

    host = lua_tolstring(L, 1, NULL);

    if (!lua_isnumber(L, 2)) {
        lua_pushstring(L, "luafcgi.New expects a integer as the second argument");
        lua_error(L);
        return 0;
    }

    port = lua_tointeger(L, 2);

    return 1;
}

static int getHost(lua_State *L) {
    lua_pushstring(L, host);
    return 1;
}

static int getPort(lua_State *L) {
    lua_pushinteger(L, port);
    return 1;
}

LUALIB_API int luaopen_luafcgi(lua_State *L) {
    struct luaL_Reg driver[] = {
        {"New", New},
        {"getHost", getHost},
        {"getPort", getPort},
        {NULL, NULL},
    };

    luaL_register(L, "luafcgi", driver);
    return 1;
}
