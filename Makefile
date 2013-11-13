LUA_INC= /usr/include/lua5.1

#WARN= -Wall -Wmissing-prototypes -Wmissing-declarations -ansi -pedantic

WARN= -Wall
INCS= -I$(LUA_INC)
CFLAGS= -fPIC -O2 $(WARN) $(INCS) $(DEFS)
CXXFLAGS= -O2 $(WARN) $(INCS) $(DEFS)
CC= gcc

LIB_OPTION= -shared

LIBNAME= luafcgi.so

OBJS= src/luafcgi.o
SRCS= src/luafcgi.c

lib: $(LIBNAME)

$(LIBNAME): $(OBJS)
	$(CC) $(CFLAGS) -o bin/$@ $(LIB_OPTION) $(OBJS)

clean:
	rm -f bin/$(LIBNAME) src/*.o
