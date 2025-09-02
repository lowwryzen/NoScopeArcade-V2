init:
	gcc src/main.c -o main.exe -I include -L lib -lraylib -lwinmm -lgdi32 -luser32 && main