#ifndef LUAFCGI_FUNCTIONS_URL_H
#define LUAFCGI_FUNCTIONS_URL_H
char from_hex(char ch);
char to_hex(char code);
char *urlencode(char *str);
char *urldecode(char *str);
#endif
