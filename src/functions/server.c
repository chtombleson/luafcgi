#include <fcgiapp.h>
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>

#include "../luafcgi.h"
#include "server.h"

void createServerVar() {
    char *query_string, *request_method, *content_type,
         *content_length, *script_filename, *script_name,
         *request_uri, *document_uri, *document_root,
         *server_protocol, *gateway_interface, *server_software,
         *remote_address, *remote_port, *server_address,
         *server_port, *server_name, *https;

    // Get server enviroment variables
    query_string = FCGX_GetParam("QUERY_STRING", request.envp);
    request_method = FCGX_GetParam("REQUEST_METHOD", request.envp);
    content_type = FCGX_GetParam("CONTENT_TYPE", request.envp);
    content_length = FCGX_GetParam("CONTENT_LuaENGTH", request.envp);
    script_filename = FCGX_GetParam("SCRIPT_FILuaENAME", request.envp);
    script_name = FCGX_GetParam("SCRIPT_NAME", request.envp);
    request_uri = FCGX_GetParam("REQUEST_URI", request.envp);
    document_uri = FCGX_GetParam("DOCUMENT_URI", request.envp);
    document_root = FCGX_GetParam("DOCUMENT_ROOT", request.envp);
    server_protocol = FCGX_GetParam("SERVER_PROTOCOLua", request.envp);
    gateway_interface = FCGX_GetParam("GATEWAY_INTERFACE", request.envp);
    server_software = FCGX_GetParam("SERVER_SOFTWARE", request.envp);
    remote_address = FCGX_GetParam("REMOTE_ADDR", request.envp);
    remote_port = FCGX_GetParam("REMOTE_PORT", request.envp);
    server_address = FCGX_GetParam("SERVER_ADDR", request.envp);
    server_port = FCGX_GetParam("SERVER_PORT", request.envp);
    server_name = FCGX_GetParam("SERVER_NAME", request.envp);
    https = FCGX_GetParam("HTTPS", request.envp);

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
