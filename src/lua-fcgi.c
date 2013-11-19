#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

typedef struct {
    const char* socket;
    int threads;
}Config;

Config* options(int argc, const char* argv[]) {
    Config conf;
    Config *config;
    int i;

    for (i=0; i < argc; i++) {
        if (argv[i] == "-socket") {
            conf.socket = argv[(i + 1)];
        } else if (argv[i] == "-threads") {
            conf.threads = argv[(i + 1)];
        }
    }

    if (!conf.threads) {
        conf.threads = 4;
    }

    config = &conf;
    return config;
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("Usage: lua-fcgi -socket SOCKET PATH [-threads]\n");
        printf("\t-socket: Socket path\n");
        printf("\t-threads: Number of threads to spawn (Default is 4)\n");
        return 1;
    }

    Config *config = options(argc, argv);
    printf("Socket: %s\n", config->socket);
    printf("Threads: %d\n", config->threads);


    return 0;
}
