The crawler will recursively download all unique pages starting from a seed
page (default to https://web.cs.dartmouth.edu). The downloaded pages are
saved in files named by an integer id. The first line in each file is the URL.

The default search depth is 2.

**USAGE** ./crawler [(-h | --help) | URL]

### TO BUILD 

To build the crawler

goto /src/crawler/ and type "make"
