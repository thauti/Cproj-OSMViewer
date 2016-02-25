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
<<<<<<< HEAD
	$(CC) $(CFLAGS) -o $@ $^ -lxml2 -lgtk-3 -lcairo -lgio-2.0 -lgobject-2.0 -lglib-2.0
=======
	$(CC) -o $@ $(CFLAGS) $^
>>>>>>> cab08f10c9ea799d4e7a9c36b28081d6004b1e56

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)
