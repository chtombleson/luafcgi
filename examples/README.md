# LuaFCGI Examples

This directory contains some example lua FCGI scripts.

## Usage

First compile luafcgi and install nginx & spawn fcgi

Example nginx config (/etc/nginx/sites-available/luafcgi):

    server {
        listen 80;
        server_name localhost;
        root [PATH TO LUAFCGI]/examples;
        index index.lua;

        location / {
            try_files $uri /index.lua;
            include fastcgi_params;
            fastcgi_pass 127.0.0.1:9000;
        }
    }

Start the fcgi process using spawn-fcgi:

    $ spawn-fcgi -a 127.0.0.1 -p 9000 [PATH TO LUAFGCI]/bin/luafcgi

Now in a web browser goto http://localhost this will serve the index.lua
script. To view the other files for example server.lua goto http://localhost/server.lua
