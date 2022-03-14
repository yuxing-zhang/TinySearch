CC = clang
OBJ = crawler.o ../utils/html.o ../utils/dict.o ../utils/hash.o

crawler : $(OBJ)
	$(CC) -o crawler $(OBJ)

crawler.o : crawler.h ../utils/html.h ../utils/dict.h

clean :
	rm crawler.o
