CC=gcc
DEBUG=-g
WARN=-Wall
OUTPUT=ctOS
PROGRAM=main.c
COMPLEMENTS_PROGRAM=citroen.c toyota.c renault.c crc.c encoders.c tpms_structs.c converter.c controller.c transmiter.c gui.c -lm
MULTITHREADS=-lpthread
MATH=-lm
INLCUDE_GTK=`pkg-config --libs --cflags gtk+-3.0`

all:
	$(CC) $(DEBUG) $(WARN) $(PROGRAM) $(COMPLEMENTS_PROGRAM) $(INLCUDE_GTK) $(MULTITHREADS) $(MATH) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

