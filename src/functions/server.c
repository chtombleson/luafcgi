#include <fcgiapp.h>
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>

#include "../luafcgi.h"
#include "server_info.h"
#include "server.h"

void serverVar() {
    LuaFCGI_ServerInfo serverInfo = getServerInfo();

    // Create table to hold these values for Lua to read from
    lua_createtable(Lua, 0, 0);

    lua_pushstring(Lua, "query_string");
    lua_pushstring(Lua, serverInfo.query_string);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "request_method");
    lua_pushstring(Lua, serverInfo.request_method);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "content_type");
    lua_pushstring(Lua, serverInfo.content_type);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "content_length");
    lua_pushstring(Lua, serverInfo.content_length);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "script_filename");
    lua_pushstring(Lua, serverInfo.script_filename);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "script_name");
    lua_pushstring(Lua, serverInfo.script_name);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "request_uri");
    lua_pushstring(Lua, serverInfo.request_uri);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "document_uri");
    lua_pushstring(Lua, serverInfo.document_uri);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "document_root");
    lua_pushstring(Lua, serverInfo.document_root);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "server_protocol");
    lua_pushstring(Lua, serverInfo.server_protocol);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "gateway_interface");
    lua_pushstring(Lua, serverInfo.gateway_interface);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "server_software");
    lua_pushstring(Lua, serverInfo.server_software);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "remote_address");
    lua_pushstring(Lua, serverInfo.remote_address);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "remote_port");
    lua_pushstring(Lua, serverInfo.remote_port);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "server_address");
    lua_pushstring(Lua, serverInfo.server_address);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "server_port");
    lua_pushstring(Lua, serverInfo.server_port);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "server_name");
    lua_pushstring(Lua, serverInfo.server_name);
    lua_rawset(Lua, -3);

    lua_pushstring(Lua, "https");
    lua_pushstring(Lua, serverInfo.https);
    lua_rawset(Lua, -3);

    // Set table as SERVER variable in lua
    lua_setglobal(Lua, "SERVER");
}
