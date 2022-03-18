CC = clang
CFLAGS = -Wall -pedantic -std=c99 -I $(INC)
INC = ../../include/
BIN = ../../bin/indexer
LIB = ../../lib/libtseutils.a

$(BIN) : indexer.o $(LIB)
	mkdir -p ../../bin
	$(CC) -o $(BIN) $(CFLAGS) $^

indexer.o : $(INC)indexer.h $(INC)html.h $(INC)dict.h

clean :
	rm indexer.o $(BIN)
