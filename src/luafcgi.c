#include "luafcgi.h"
#include "functions/print.h"
#include "functions/server.h"


int main() {
    Lua = luaL_newstate();
    luaL_openlibs(Lua);

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    int status;

    while (FCGX_Accept_r(&request) == 0) {
        // Get filepath of lua script to run
        const char *filename = FCGX_GetParam("SCRIPT_FILENAME", request.envp);

        // Make sure the file actually exists
        int exists = access(filename, F_OK);

        if (exists == 0) {
            // Load lua script to run
            status = luaL_loadfile(Lua, filename);

            if (status) {
                FCGX_FPrintF(request.err, "Couldn't load file: %s\n", lua_tostring(Lua, -1));
            } else {
                // Override lua's default print function
                lua_pushcfunction(Lua, l_print);
                lua_setglobal(Lua, "print");

                // Add print_error function to lua (prints to stderr)
                lua_pushcfunction(Lua, l_print_error);
                lua_setglobal(Lua, "print_error");

                // Set SERVER var for lua
                serverVar();

                int result = lua_pcall(Lua, 0, LUA_MULTRET, 0);
                if (result) {
                    FCGX_FPrintF(request.err, "Failed to run script: %s\n", lua_tostring(Lua, -1));
                }
            }
        } else {
             FCGX_FPrintF(request.err, "File does not exist: %s\n", filename);
        }

        FCGX_Finish_r(&request);
    }

    lua_close(Lua);
    return 0;
}
