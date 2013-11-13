#include "luafcgi.h"

static int New(lua_State *L) {
    return 0;
}

LUALIB_API int luaopen_luafcgi(lua_State *L) {
    struct luaL_Reg driver[] = {
        {"New", New},
        {NULL, NULL},
    };

    luaL_register(L, "luafcgi", driver);
    return 1;
}
