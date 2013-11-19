#include "luafcgi.h"

static int New(lua_State *L) {
    int arg_n = lua_gettop(L);

    if (arg_n > 1) {
        lua_pushstring(L, "luafcgi.New takes 1 argument");
        lua_error(L);
        return 0;
    }

    if (!lua_isstring(L, 1)) {
        lua_pushstring(L, "luafcgi.New expects a string as the first argument");
        lua_error(L);
        return 0;
    }

    socket_path = lua_tolstring(L, 1, NULL);

    return 1;
}

static int runApp(lua_State *L) {
    int init = FCGX_Init();

    if (init != 0) {
        lua_pushstring(L, "Unable to init fastcgi library");
        lua_error(L);
        return 0;
    }

    if (socket == NULL) {
        socket = FCGX_OpenSocket(socket_path, 10);
    }

    if (socket == -1) {
        lua_pushstring(L, "Unable to open socket");
        lua_error(L);
        return 0;
    }

    return 1;
}

LUALIB_API int luaopen_luafcgi(lua_State *L) {
    struct luaL_Reg driver[] = {
        {"New", New},
        {"runApp", runApp},
        {NULL, NULL},
    };

    luaL_register(L, "luafcgi", driver);
    return 1;
}
