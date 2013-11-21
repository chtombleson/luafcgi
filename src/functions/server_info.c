#include <fcgiapp.h>
#include <stdio.h>
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>

#include "../luafcgi.h"
#include "server_info.h"

LuaFCGI_ServerInfo getServerInfo() {
    LuaFCGI_ServerInfo serverInfo;

    // Get server enviroment variables
    serverInfo.query_string = FCGX_GetParam("QUERY_STRING", request.envp);
    serverInfo.request_method = FCGX_GetParam("REQUEST_METHOD", request.envp);
    serverInfo.content_type = FCGX_GetParam("CONTENT_TYPE", request.envp);
    serverInfo.content_length = FCGX_GetParam("CONTENT_LuaENGTH", request.envp);
    serverInfo.script_filename = FCGX_GetParam("SCRIPT_FILuaENAME", request.envp);
    serverInfo.script_name = FCGX_GetParam("SCRIPT_NAME", request.envp);
    serverInfo.request_uri = FCGX_GetParam("REQUEST_URI", request.envp);
    serverInfo.document_uri = FCGX_GetParam("DOCUMENT_URI", request.envp);
    serverInfo.document_root = FCGX_GetParam("DOCUMENT_ROOT", request.envp);
    serverInfo.server_protocol = FCGX_GetParam("SERVER_PROTOCOLua", request.envp);
    serverInfo.gateway_interface = FCGX_GetParam("GATEWAY_INTERFACE", request.envp);
    serverInfo.server_software = FCGX_GetParam("SERVER_SOFTWARE", request.envp);
    serverInfo.remote_address = FCGX_GetParam("REMOTE_ADDR", request.envp);
    serverInfo.remote_port = FCGX_GetParam("REMOTE_PORT", request.envp);
    serverInfo.server_address = FCGX_GetParam("SERVER_ADDR", request.envp);
    serverInfo.server_port = FCGX_GetParam("SERVER_PORT", request.envp);
    serverInfo.server_name = FCGX_GetParam("SERVER_NAME", request.envp);
    serverInfo.https = FCGX_GetParam("HTTPS", request.envp);

    //LuaFCGI_ServerInfo *s = &serverInfo;
    return serverInfo;
}

LuaFCGI_LuaInfo getLuaInfo() {
    LuaFCGI_LuaInfo luaInfo;

    // Get Lua info
    luaInfo.version = LUA_VERSION;
    luaInfo.release = LUA_RELEASE;
    luaInfo.copyright = LUA_COPYRIGHT;
    luaInfo.authors = LUA_AUTHORS;
    luaInfo.version_num = LUA_VERSION_NUM;

    //LuaFCGI_LuaInfo *l = &luaInfo;
    return luaInfo;
}

LuaFCGI_Info getLuaFcgiInfo() {
    LuaFCGI_Info luafcgiInfo;

    // Get Lua FCGI info
    luafcgiInfo.version = LUAFCGI_VERSION;
    luafcgiInfo.release = LUAFCGI_RELEASE;
    luafcgiInfo.copyright = LUAFCGI_COPYRIGHT;
    luafcgiInfo.authors = LUAFCGI_AUTHORS;
    luafcgiInfo.version_num = LUAFCGI_VERSION_NUM;

    //LuaFCGI_Info *lfcgi = &luafcgiInfo;
    return luafcgiInfo;
}

int l_server_info(lua_State *L) {
    LuaFCGI_ServerInfo serverInfo = getServerInfo();
    LuaFCGI_LuaInfo luaInfo = getLuaInfo();
    LuaFCGI_Info luafcgiInfo = getLuaFcgiInfo();

    FCGX_FPrintF(request.out,
        "Content-type: text/html\r\n"
        "\r\n"
        "<!DOCTYPE html>\n"
        "<html>\n"
        "\t<head>\n"
        "\t\t<title>Lua FCGI | Server Info</title>\n"
        "\t</head>\n"
        "\t<body>\n"
        "\t\t<h1 style=\"display: none;\">Lua FCGI | Server Info</h1>\n"
        "\t\t<h2>Lua FCGI</h2>\n"
        "\t\t<table>\n"
        "\t\t\t<tbody>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Lua Fcgi Version</th>"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Lua Fcgi Release</th>"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Lua Fcgi Version Number</th>"
        "\t\t\t\t\t<td>%d</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Lua Fcgi Authors</th>"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Lua Fcgi Copyright</th>"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t</tbody>\n"
        "\t\t</table>\n"
        "\t\t<h2>Lua</h2>\n"
        "\t\t<table>\n"
        "\t\t\t<tbody>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Lua Version</th>"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Lua Release</th>"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Lua Version Number</th>"
        "\t\t\t\t\t<td>%d</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Lua Authors</th>"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Lua Copyright</th>"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t</tbody>\n"
        "\t\t</table>\n"
        "\t\t<h2>Server Info</h2>\n"
        "\t\t<table>\n"
        "\t\t\t<tbody>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Server Name</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Server Address</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Server Port</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Server Software</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Server Protocol</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Gateway Interface</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>HTTPS</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Request Method</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Request URI</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Query String</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Document Root</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Document URI</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Script Name</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Script Filename</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Remote Address</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Remote Port</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Content Type</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t\t<tr>\n"
        "\t\t\t\t\t<th>Content Length</th>\n"
        "\t\t\t\t\t<td>%s</td>\n"
        "\t\t\t\t</tr>\n"
        "\t\t\t</tbody>\n"
        "\t\t</table>\n"
        "\t</body>\n"
        "</html>",
        luafcgiInfo.version,
        luafcgiInfo.release,
        luafcgiInfo.version_num,
        luafcgiInfo.authors,
        luafcgiInfo.copyright,
        luaInfo.version,
        luaInfo.release,
        luaInfo.version_num,
        luaInfo.authors,
        luaInfo.copyright,
        serverInfo.server_name,
        serverInfo.server_address,
        serverInfo.server_port,
        serverInfo.server_software,
        serverInfo.server_protocol,
        serverInfo.gateway_interface,
        serverInfo.https,
        serverInfo.request_method,
        serverInfo.request_uri,
        serverInfo.query_string,
        serverInfo.document_root,
        serverInfo.document_uri,
        serverInfo.script_name,
        serverInfo.script_filename,
        serverInfo.remote_address,
        serverInfo.remote_port,
        serverInfo.content_type,
        serverInfo.content_length
    );

    return 1;
}
