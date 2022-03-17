#!/bin/bash
# This script automatically:
# 1 build the crawler, indexer and query engine
# 2 test the query engine against predefined cases
# 3 if tests are passed, run the query engine

make

echo "Start crawling..."
./bin/crawler
echo "Crawling done!"

echo "Building index"
./bin/indexer
echo "Index successfully built!"

./bin/engine
