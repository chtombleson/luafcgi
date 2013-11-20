LUA_INC= /usr/include/lua5.1

#WARN= -Wall -Wmissing-prototypes -Wmissing-declarations -ansi -pedantic

WARN= -Wall
INCS= -I$(LUA_INC)
LIBS= -lfcgi -llua5.1 -lm
CFLAGS= -fPIC -O2 $(WARN) $(INCS) $(DEFS)
CXXFLAGS= -O2 $(WARN) $(INCS) $(DEFS)
CC= gcc

SRCS= src/luafcgi.c
EXE= luafcgi

lib: $(EXE)

$(EXE):
	$(CC) $(WARN) $(INCS) -L/usr/lib/i386-linux-gnu/ -o bin/$@ $(SRCS) $(LIBS)

clean:
	rm -f bin/$(EXE)
