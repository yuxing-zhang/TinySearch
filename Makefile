all : utils crawler indexer

utils :
	$(MAKE) -C src/utils

crawler :
	$(MAKE) -C src/crawler

indexer :
	$(MAKE) -C src/indexer
