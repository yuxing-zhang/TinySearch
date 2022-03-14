CC = clang
OBJ = crawler.o ../utils/html.o ../utils/dict.o ../utils/hash.o
bin = ../../bin/crawler

$(bin) : $(OBJ)
	mkdir -p ../../bin
	$(CC) -o $(bin) $(OBJ)

crawler.o : crawler.h ../utils/html.h ../utils/dict.h

clean :
	rm crawler.o
