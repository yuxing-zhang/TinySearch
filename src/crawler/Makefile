CC = clang
OBJ = crawler.o html.o dict.o hash.o

crawler : $(OBJ)
	$(CC) -o crawler $(OBJ)

crawler.o : crawler.h html.h dict.h
html.o : html.h
dict.o : dict.h hash.h
hash.o :

clean :
	rm $(OBJ)
