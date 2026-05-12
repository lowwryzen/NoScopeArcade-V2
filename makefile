CC      = gcc
CFILES  := $(wildcard src/*/*.c)

RAYLIB  = raylib
INCLUDE = include
LIB     = raylib -lraylib -lwinmm -lgdi32 -luser32

OUTPUT  = main.exe
EXEC    = ./main

compile:
	$(CC) src/main.c $(CFILES) -o $(OUTPUT) -I$(RAYLIB) -I$(INCLUDE) -L $(LIB)

run:
	./main

all: compile run