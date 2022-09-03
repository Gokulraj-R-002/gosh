CC=gcc
CFLAGS=-I.
DEPS = header.h prompt.h
OBJ = main.c prompt.c parse_input.c basic_commands.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gosh: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS) 
