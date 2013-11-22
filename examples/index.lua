-- index.lua
print("Content-type: text/html\r\n")
print("\r\n")
print("<html>\n")
print("\t<head>\n")
print("\t\t<title>Lua FCGI example</title>\n");
print("\t</head>\n")
print("\t<body>\n")
print("\t\t<strong>Hello World</strong>\n")
print("\t\t<strong>Server Name: </strong>"..SERVER["server_name"].."\n")
print("\t</body>\n")
print("</html>")
