EXEC = osm
CC = gcc
CFLAGS = `xml2-config --cflags` `xml2-config --libs` `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
BDIR = $(binaries)
ODIR = $(obj)
HDIR = $(headers)
HEAD = parse.h osm.h
OBJL = abr.o parse.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(OBJL))

EXEC = osm

all: $(BDIR)/$(EXEC)

osm: $(OBJL)
	 $(CC) -o $@ $^ $(CFLAGS)

%(ODIR)/%.o: %.c $(HEAD)
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)