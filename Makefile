CC=gcc
CFLAGS=-lpthread


all: shell

shell: shell.c
	$(CC)  shell.c -o shell $(CFLAGS)
	
clean:
	rm -rf *o shell