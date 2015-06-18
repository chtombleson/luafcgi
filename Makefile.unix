LUA_INC= /usr/include/

#WARN= -Wall -Wmissing-prototypes -Wmissing-declarations -ansi -pedantic

WARN= -Wall
INCS= -I$(LUA_INC)
LIBS= -lfcgi -llua5.1 -lm
CFLAGS= -fPIC -O2 $(WARN) $(INCS) $(DEFS)
CXXFLAGS= -O2 $(WARN) $(INCS) $(DEFS)
CC= gcc

SRCS= src/main.c src/luafcgi/functions/print.c src/luafcgi/functions/server.c src/luafcgi/functions/server_info.c src/luafcgi/luafcgi.c src/deps/commander-1.3.2/src/commander.c

EXE= luafcgi

lib: $(EXE)

$(EXE):
	$(CC) $(WARN) -L/usr/lib/ -o bin/$@ $(SRCS) $(LIBS) -std=c99

clean:
	rm -f bin/$(EXE)

install:
	cp bin/$(EXE) /usr/local/bin/

uninstall:
	rm /usr/local/bin/$(EXE)
