#ifndef LUAFCGI_FUNCTIONS_GET_H
#define LUAFCGI_FUNCTIONS_GET_H
typedef struct {
    char *key, *value;
} getParam;

getParam* parseQueryString(char *query_string);
void getVar();
#endif
