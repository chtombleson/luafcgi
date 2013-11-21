#include <fcgiapp.h>
#include <stdio.h>
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>

#include "../luafcgi.h"
#include "print.h"

static int l_print(lua_State *L) {
    int arg_n = lua_gettop(L);

    if (arg_n > 1) {
        lua_pushstring(L, "print takes one argument");
        lua_error(L);
        return 0;
    }

    const char* str = lua_tostring(L, 1);
    FCGX_FPrintF(request.out, str);
    return 1;
}

static int l_print_error(lua_State *L) {
    int arg_n = lua_gettop(L);

    if (arg_n > 1) {
        lua_pushstring(L, "print_error takes one argument");
        lua_error(L);
        return 0;
    }

    const char* str = lua_tostring(L, 1);
    FCGX_FPrintF(request.err, str);
    return 1;
}
