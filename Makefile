all : utils crawler indexer engine

utils :
	$(MAKE) -C src/utils

crawler :
	$(MAKE) -C src/crawler

indexer :
	$(MAKE) -C src/indexer

engine :
	$(MAKE) -C src/engine

clean :
	$(MAKE) clean -C src/utils
	$(MAKE) clean -C src/crawler
	$(MAKE) clean -C src/indexer
	$(MAKE) clean -C src/engine
