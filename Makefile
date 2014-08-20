# SlideScript makefile
# (C) Copyright 2014 Chris Dorman, some rights reserved (CC-BY-SA 3.0)

PREFIX ?= /usr/local

CC           ?= cc
CFLAGS       += -O2 -std=c99 -pedantic -g -Wall -Wextra --param=ssp-buffer-size=2 -fstack-protector-all
CPPFLAGS     ?= -D_FORTIFY_SOURCE=2
LDFLAGS      ?= -Wl,-O1,--sort-common,--hash-style=gnu,-z,relro
BIN          ?= slidescript

OBJECTS = main.o

all: main

fresh: clean all

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN) $(LDFLAGS) $(CFLAGS)
	
clean:
	rm -f $(OBJECTS) $(BIN)
	
install:
	install -D $(BIN) $(DESTDIR)/$(PREFIX)/bin/$(BIN)

