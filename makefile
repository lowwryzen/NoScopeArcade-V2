CC      = gcc
CFILES  = src/main.c src/moveset.c src/vector.c
OUTPUT  = main.exe
INCLUDE = include
LIB     = lib -lraylib -lwinmm -lgdi32 -luser32
EXEC    = ./main

init:
	$(CC) $(CFILES) -o $(OUTPUT) -I $(INCLUDE) -L $(LIB) && $(EXEC)