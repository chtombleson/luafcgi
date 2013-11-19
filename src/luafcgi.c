/*
* The MIT License (MIT)
*
* Copyright (c) 2013 Christopher Tombleson <chris@cribznetwork.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
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
