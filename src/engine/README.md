The search engine carries search against the index built with the indexer. Currently only supports intersection of indefinite # of search terms.

The results are ranked by the total number of occurrence of every search term.
```
rank(page) = \sum_{word} # of occurrence of word in page
```
If any term is not contained in any webpage, or no search term is provided, the engine will simply return nothing.

### TO BUILD 

To build the search engine

goto /src/engine/ and type "make"
