#include <stdio.h>
#include "deps/commander-1.3.2/src/commander.h"

static void config(command_t *self) {}

int main(int argc, char **argv) {
    command_t cmd;
    command_init(&cmd, argv[0], "0.0.1");
    command_option(&cmd, "-c", "--config", "configuration file", config);
    command_parse(&cmd, argc, argv);

    command_free(&cmd);
    return 0;
}

