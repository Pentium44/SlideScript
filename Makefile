# SlideScript makefile
# (C) Copyright 2014 Chris Dorman, some rights reserved (GPLv3)
CC=gcc
FLAGS=
EXEC=slidescript


all: main

main: src
	$(CC) main.o -o $(EXEC) $(FLAGS)
	
src:
	$(CC) -c main.c $(FLAGS)

clean:
	rm *o $(EXEC)
	
install:
	cp $(EXEC) /usr/bin
