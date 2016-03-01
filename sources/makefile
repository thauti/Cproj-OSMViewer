CC = gcc
CFLAGS = -I ../include `xml2-config --cflags` `xml2-config --libs` `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
EXEC = osm
HEADERS = window.h parse.h osm.h 
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)
	mkdir -p ../bin/ ../bin/obj
	mv osm ../bin/
	mv *.o ../bin/obj

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lxml2 -lgtk-3 -lcairo -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lm


%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)
