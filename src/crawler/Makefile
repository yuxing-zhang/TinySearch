CC = clang
CFLAGS = -Wall -pedantic -std=c99 -I $(INC)
INC = ../../include/
LIB = ../../lib/libtseutils.a
BIN = ../../bin/crawler

$(BIN) : crawler.o $(LIB)
	mkdir -p ../../bin
	$(CC) -o $(BIN) $(CFLAGS) $^

crawler.o : $(INC)crawler.h $(INC)html.h $(INC)dict.h

clean :
	rm crawler.o $(BIN)
