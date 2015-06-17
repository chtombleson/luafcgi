LUA_INC= /usr/include/

#WARN= -Wall -Wmissing-prototypes -Wmissing-declarations -ansi -pedantic

WARN= -Wall
INCS= -I$(LUA_INC)
LIBS= -lfcgi -llua5.1 -lm
CFLAGS= -fPIC -O2 $(WARN) $(INCS) $(DEFS)
CXXFLAGS= -O2 $(WARN) $(INCS) $(DEFS)
CC= gcc

SRCS= src/luafcgi/functions/print.c src/luafcgi/functions/server.c src/luafcgi/functions/server_info.c src/luafcgi/luafcgi.c
EXE= luafcgi

lib: $(EXE)

$(EXE):
	$(CC) $(WARN) -L/usr/lib/ -o bin/$@ $(SRCS) $(LIBS)

clean:
	rm -f bin/$(EXE)

install:
	cp bin/$(EXE) /usr/local/bin/

uninstall:
	rm /usr/local/bin/$(EXE)
