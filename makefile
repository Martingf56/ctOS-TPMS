CC=gcc
DEBUG=-g
OUTPUT=ctOS
PROGRAM=main.c
COMPLEMENTS_PROGRAM=citroen.c toyota.c crc.c encoders.c tpms_structs.c converter.c

all:
	$(CC) $(DEBUG) $(PROGRAM) $(COMPLEMENTS_PROGRAM) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

