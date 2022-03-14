obj = indexer.o ../utils/html.o ../utils/dict.o ../utils/hash.o
cc = clang

indexer : $(obj)
	$(cc) -o indexer $(obj)

indexer.o : indexer.h ../utils/html.h ../utils/dict.h

clean :
	rm indexer.o
