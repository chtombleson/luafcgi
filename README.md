# Lua FCGI

Lua Fast CGI module.

**Tested on ubuntu**

## Dependencies

There are 2 dependencies needed to build this project
they are:

 * Lua 5.1 development
 * Fast CGI development

You can run the following command to install dependencies

    $ sudo apt-get install liblua5.1-0-dev libfcgi-dev spawn-fcgi lua5.1
    $ ./install_dependencies.sh

## Building

If your building on 64bit and it fails you may have to edit the Makefile
to point at the right location for the liblua5.1.so file.

    $ make

## Running Luafcgi

Install spawn-fcgi to run the fcgi process: `$ sudo apt-get install spawn-fcgi`

    $ spawn-fcgi -a 127.0.0.1 -p 9000 bin/luafcgi

## Nginx Setup

    $ sudo apt-get install nginx

Example configuration:

    server {
        listen 80;
        server_name localhost;
        root /home/www/lua;
        index index.lua;

        location / {
            try_files $uri /index.lua;
            include fastcgi_params;
            fastcgi_pass 127.0.0.1:9000;
        }
    }

On some version of nginx you will need to modify
/etc/nginx/fastcgi_params:

    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;

## Examples

For example lua scripts see examples directory.

## LICENSE

See LICENSE
