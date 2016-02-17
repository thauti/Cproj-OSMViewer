CC = gcc
CFLAGS = `xml2-config --cflags` `xml2-config --libs` `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
EXEC = osm

all: $(EXEC)
osm: main.o abr.o parse.o 
	$(CC) -o $@ $^ $(CFLAGS)

abr.o: osm.h
parse.o: parse.h osm.h
main.o: parse.h osm.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)