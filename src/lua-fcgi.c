#include "fcgiapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

// Global vars
FCGX_Request request;
lua_State *Lua;

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

int main() {
    Lua = luaL_newstate();
    luaL_openlibs(Lua);

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    int status;

    while (FCGX_Accept_r(&request) == 0) {
        // Get filepath of lua script to run
        char *filename = FCGX_GetParam("SCRIPT_FILENAME", request.envp);
        char *docroot = FCGX_GetParam("DOCUMENT_ROOT", request.envp);
        char *filepath[(strlen(docroot) + strlen(filename) + 1)];
        strcpy(filepath, docroot);
        strcat(filepath, filename);

        // Make sure the file actually exists
        int exists = access(filepath, F_OK);

        if (exists == 0) {
            // Load lua script to run
            status = luaL_loadfile(L, filepath);

            if (status) {
                FCGX_FPrintF(request.err, "Couldn't load file: %s\n", lua_tostring(L, -1));
            } else {
                createServerVar();
            }

            /*FCGX_FPrintF(request.out, 
                "Content-type: text/html\r\n"
                "\r\n"
                "<html>\n"
                "\t<head>\n"
                "\t<title>Hello, World!</title>\n"
                "\t</head>\n"
                "\t<body>\n"
                "\t\t<h1>Hello, World!</h1>\n"
                "\t</body>\n"
                "</html>\n"
            );*/
        } else {
             FCGX_FPrintF(request.err, "File does not exist: %s\n", filepath);
        }

        FCGX_Finish_r(&request);
    }

    lua_close(Lua);
    return 0;
}
