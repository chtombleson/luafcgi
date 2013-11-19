/*
* The MIT License (MIT)
*
* Copyright (c) 2013 Christopher Tombleson <chris@cribznetwork.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include "lua-fcgi.h"


/**
* parseArgs
*
* Parse the command line arguments that where given
* @param int            argc    Argument count
* @param const char*    argv    Array of arguments
* @return void
*/
void parseArgs(int argc, const char* argv[]) {
    int key;

    while ((key = getopt(argc, argv, "c:")) != -1) {
        switch (key) {
            case 'c':
                config_file = optarg;
                break;
        }
    }
}


/**
* readConfig
*
* Read the configuration file
* @return int 0 on failure, 1 on success
*/
int readConfig() {
    config_init(&cfg);

    if (!config_read_file(&cfg, config_file)) {
        printf("Error reading config file\n");
        config_destroy(&cfg);
        return 0;
    }

    if (!config_lookup_string(&cfg, "socket", &socket)) {
        printf("No 'socket' setting in configuration file\n");
        return 0;
    }

    config_lookup_int(&cfg, "threads", &threads);

    if (!threads) {
        threads = 4;
    }

    return 1;
}


/**
* main
*
* The main function that runs the program
* @param int            argc    Argument count
* @param const char*    argv    Array of arguments
* @return int 0 on success, anything else on failure
*/
int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("Usage: lua-fcgi -c CONFIG FILE\n");
        printf("\t-c: config file\n");
        return -1;
    }

    parseArgs(argc, argv);

    if (!readConfig()) {
        return -1;
    }

    printf("Socket: %s\n", socket);
    printf("Threads: %d\n", threads);

    config_destroy(&cfg);
    return 0;
}
