cc = clang
obj = engine.o ../utils/dict.o ../utils/html.o ../utils/hash.o
bin = ../../bin/engine

$(bin) : $(obj)
	mkdir -p ../../bin
	$(cc) -o $(bin) $(obj)

engine.o : engine.h ../utils/dict.h ../utils/html.h ../indexer/indexer.h

clean :
	rm engine.o
