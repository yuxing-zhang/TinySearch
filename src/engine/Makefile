CC = clang
CFLAGS = -Wall -pedantic -std=c99 -I $(INC)
INC = ../../include/
BIN = ../../bin/engine
LIB = ../../lib/libtseutils.a

$(BIN) : engine.o $(LIB)
	mkdir -p ../../bin
	$(CC) -o $(BIN) $(CFLAGS) $^

engine.o : $(INC)engine.h $(INC)dict.h $(INC)html.h $(INC)indexer.h

clean :
	rm engine.o $(BIN)
