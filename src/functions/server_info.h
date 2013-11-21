#include <lua5.1/lua.h>

#ifndef LUAFGGI_FUNCTIONS_SERVER_INFO_H
#define LUAFGGI_FUNCTIONS_SERVER_INFO_H
typedef struct {
    char *query_string, *request_method, *content_type,
         *content_length, *script_filename, *script_name,
         *request_uri, *document_uri, *document_root,
         *server_protocol, *gateway_interface, *server_software,
         *remote_address, *remote_port, *server_address,
         *server_port, *server_name, *https;
} LuaFCGI_ServerInfo;

typedef struct {
    const char *version, *release, *copyright, *authors;
    int version_num;
} LuaFCGI_LuaInfo;

typedef struct {
    const char *version, *release, *copyright, *authors;
    int version_num;
} LuaFCGI_Info;

LuaFCGI_ServerInfo getServerInfo();
LuaFCGI_LuaInfo getLuaInfo();
LuaFCGI_Info getLuaFcgiInfo();
int l_server_info(lua_State *L);
#endif
