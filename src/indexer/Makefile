obj = indexer.o ../utils/html.o ../utils/dict.o ../utils/hash.o
cc = clang
bin = ../../bin/indexer

$(bin) : $(obj)
	mkdir -p ../../bin
	$(cc) -o $(bin) $(obj)

indexer.o : indexer.h ../utils/html.h ../utils/dict.h

clean :
	rm indexer.o
