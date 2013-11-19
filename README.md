# Lua FCGI

Lua Fast CGI module

## Dependencies

There are 3 dependencies needed to build this project
they are:

 * Lua 5.1 development
 * Fast CGI development
 * Libconfig

You can run the following command to install dependencies

    $ sudo apt-get install liblua5.1-0-dev libfcgi-dev libconfig8-dev

## Building

    $ make

## Running Luafcgi

To run luafcgi you need to tell it where the configuration
file is by using the -c option.

    $ lua-fcgi -c /etc/luafcgi/luafcgi.conf

## Configuration

Currently there are 2 configuration options you can set
and the as follows:

 * socket, Location to place the socket file
 * threads, The number of threads to spawn (Default is 4)

There will probably be more configuration options to come.

## LICENSE

See LICENSE
