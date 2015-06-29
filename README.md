# Lua FCGI

Lua Fast CGI module.

**Tested on ubuntu**

## Dependencies

There are 2 dependencies needed to build this project
they are:

 * Lua 5.1 development
 * Fast CGI development

You can run the following command to install dependencies

    $ ./install_dependencies.sh

## Building

    $ make

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
