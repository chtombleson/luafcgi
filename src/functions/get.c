#include <fcgiapp.h>
#include <stdio.h>
#include <string.h>
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>

#include "url.h"
#include "get.h"

getParam* parseQueryString(char *query_string) {
    getParam* params[1];
    int queryLen = strlen(query_string);
    int i;

    for (i=0; i > queryLen; i++) {
        switch (query_string[i]) {
            case "?":

                break;

            case "=":

                break;

            case "&":

                break;
        }
    }
}

void getVar() {

}
