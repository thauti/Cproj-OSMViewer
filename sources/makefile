CC = gcc
CFLAGS = -I ../include `xml2-config --cflags` `xml2-config --libs` `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
EXEC = osm
HEADERS = parse.h osm.h
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)
	mkdir -p ../bin/
	cp osm ../bin/
	rm *.o
	rm osm

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)
