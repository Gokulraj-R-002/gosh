CC=gcc
CFLAGS=-I.
DEPS = header.h
OBJ = main.c prompt.c parse_input.c basic_commands.c list_files.c history.c pinfo.c discover.c system_commands.c colors.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gosh: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS) 
