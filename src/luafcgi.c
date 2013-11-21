#include "luafcgi.h"

void createServerVar() {
    char *query_string, *request_method, *content_type,
         *content_length, *script_filename, *script_name,
         *request_uri, *document_uri, *document_root,
         *server_protocol, *gateway_interface, *server_software,
         *remote_address, *remote_port, *server_address,
         *server_port, *server_name, *https;

    // Get server enviroment variables
    query_string        = FCGX_GetParam("QUERY_STRING", request.envp);
    request_method      = FCGX_GetParam("REQUEST_METHOD", request.envp);
    content_type        = FCGX_GetParam("CONTENT_TYPE", request.envp);
    content_length      = FCGX_GetParam("CONTENT_LENGTH", request.envp);
    script_filename     = FCGX_GetParam("SCRIPT_FILENAME", request.envp);
    script_name         = FCGX_GetParam("SCRIPT_NAME", request.envp);
    request_uri         = FCGX_GetParam("REQUEST_URI", request.envp);
    document_uri        = FCGX_GetParam("DOCUMENT_URI", request.envp);
    document_root       = FCGX_GetParam("DOCUMENT_ROOT", request.envp);
    server_protocol     = FCGX_GetParam("SERVER_PROTOCOL", request.envp);
    gateway_interface   = FCGX_GetParam("GATEWAY_INTERFACE", request.envp);
    server_software     = FCGX_GetParam("SERVER_SOFTWARE", request.envp);
    remote_address      = FCGX_GetParam("REMOTE_ADDR", request.envp);
    remote_port         = FCGX_GetParam("REMOTE_PORT", request.envp);
    server_address      = FCGX_GetParam("SERVER_ADDR", request.envp);
    server_port         = FCGX_GetParam("SERVER_PORT", request.envp);
    server_name         = FCGX_GetParam("SERVER_NAME", request.envp);
    https               = FCGX_GetParam("HTTPS", request.envp);

    // Create table to hold these values for Lua to read from
    lua_createtable(Lua, 0, 0);

    lua_pushstring(Lua, "query_string");
    lua_pushstring(Lua, query_string);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "request_method");
    lua_pushstring(Lua, request_method);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "content_type");
    lua_pushstring(Lua, content_type);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "content_length");
    lua_pushstring(Lua, content_length);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "script_filename");
    lua_pushstring(Lua, script_filename);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "script_name");
    lua_pushstring(Lua, script_name);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "request_uri");
    lua_pushstring(Lua, request_uri);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "document_uri");
    lua_pushstring(Lua, document_uri);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "document_root");
    lua_pushstring(Lua, document_root);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "server_protocol");
    lua_pushstring(Lua, server_protocol);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "gateway_interface");
    lua_pushstring(Lua, gateway_interface);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "server_software");
    lua_pushstring(Lua, server_software);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "remote_address");
    lua_pushstring(Lua, remote_address);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "remote_port");
    lua_pushstring(Lua, remote_port);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "server_address");
    lua_pushstring(Lua, server_address);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "server_port");
    lua_pushstring(Lua, server_port);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "server_name");
    lua_pushstring(Lua, server_name);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "https");
    lua_pushstring(Lua, https);
    lua_rawset(Lua, -3);

    // Set table as SERVER variable in lua
    lua_setglobal(Lua, "SERVER");
}

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
                lua_pushcfunction(Lua, l_print);
                lua_setglobal(Lua, "print");
                createServerVar();

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
