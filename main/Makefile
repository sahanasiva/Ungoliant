CC = gcc
CFLAGS = -Wall
LDFLAGS = -lxml2 -I/usr/include/libxml2 -lcurl
EXEC = cproj

all: $(EXEC)

cproj: parser.o crawler.o
	$(CC) -o cproj parser.o crawler.o $(LDFLAGS)

crawler.o: crawler.c
		$(CC) -o crawler.o -c crawler.c $(CFLAGS)

parser.o: parserHtml.c
	$(CC) -o parser.o -c parserHtml.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
	rm -r Sites/*
