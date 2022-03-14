The Indexer generates a indexing data structure from the crawled webpages. This data structure can be dumped into `../../data/index.dat` for serialization. `index.dat` contains `new-line`
separated records. Each record is of the following format.
```
word page_count id_1 occurrence_1 id_2 occurrence_2 ...
```
where `page_count` = # of pages containing `word` and `occurrence_i` = # of occurrence of `word` in html file `id_i`.

### TO BUILD

To build the indexer

goto src/indexer and type "make"
