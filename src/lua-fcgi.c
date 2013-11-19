#include <stdio.h>
#include <unistd.h>
#include <libconfig.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

typedef struct {
    const char* socket;
    int threads;
}Config;

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("Usage: lua-fcgi -c CONFIG FILE\n");
        printf("\t-c: config file\n");
        return -1;
    }

    config_t cfg;
    config_setting_t *setting;
    char *config;
    int key;

    while ((key = getopt(argc, argv, "c:")) != -1) {
        switch (key) {
            case 'c':
                config = optarg;
                break;
        }
    }

    config_init(&cfg);

    if (!config_read_file(&cfg, config)) {
        printf("Error reading config file\n");
        config_destroy(&cfg);
        return -1;
    }

    const char *socket;
    int threads;

    if (!config_lookup_string(&cfg, "socket", &socket)) {
        printf("No 'socket' setting in configuration file\n");
        return -1;
    }

    config_lookup_int(&cfg, "threads", &threads);

    if (!threads) {
        threads = 4;
    }

    printf("Socket: %s\n", socket);
    printf("Threads: %d\n", threads);

    return 0;
}
