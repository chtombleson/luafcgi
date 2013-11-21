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
