CC=gcc
DEBUG=-g
OUTPUT=script
PROGRAM=script.c

all:
	$(CC) $(DEBUG) $(PROGRAM) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

