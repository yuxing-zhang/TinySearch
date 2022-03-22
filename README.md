## The tiny search engine project
* [x] Crawler
* [x] Indexer
* [x] Query engine

### TO BUILD
Type "make". This will recursively build all components under `bin` folder.

### TO RUN
bin/crawler -> bin/indexer -> bin/engine

Alternatively, use `./build_test_run.sh` to automate the whole process.

The crawler will start downloading webpages from a seed URL, wihch can be
set in the above shell script or as a input to the crawler program. When
downloading is done, an index will be built, after which the search prompt
`Search >>> ` will appear. To quit searching, type CTRL-D or CTRL-C.

### References
* [Dartmouth CS50](https://www.cs.dartmouth.edu/~campbell/cs50/)
* [Searching the Web](
https://www.cs.dartmouth.edu/~campbell/cs50/searchingtheweb.pdf)
