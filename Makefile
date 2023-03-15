CC=g++
CFLAGS=-g -Wall
SRCFILES = $(wildcard src/*.cpp)
OBJFILES = $(patsubst src/%.cpp,obj/%.o,$(SRCFILES))


all: bin/main

clean:
	del "obj\*.o"
	del "bin\main.exe"

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -Iinclude -o $@

bin/main: $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(wildcard lib/*)