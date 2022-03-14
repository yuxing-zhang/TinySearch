obj = indexer.o html.o dict.o hash.o
cc = clang

indexer : $(obj)
	$(cc) -o indexer $(obj)

indexer.o : indexer.h html.h dict.h
html.o : html.h
dict.o : dict.h hash.h
hash.o :

clean :
	rm $(obj)
