CC=gcc
DEBUG=-g
OUTPUT=ctOS
PROGRAM=main.c
COMPLEMENTS_PROGRAM=citroen.c toyota.c crc.c encoders.c tpms_structs.c converter.c controller.c
MULTITHREADS=-lpthread
INLCUDE_GTK=`pkg-config --libs --cflags gtk+-3.0`

all:
	$(CC) $(DEBUG) $(PROGRAM) $(COMPLEMENTS_PROGRAM) $(INLCUDE_GTK) $(MULTITHREADS) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

