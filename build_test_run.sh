#!/bin/bash
# This script automatically:
# 1 build the crawler, indexer and query engine
# 2 test the query engine against predefined cases [NOT YET IMPLEMENTED]
# 3 if tests are passed, run the query engine

make

# Seed URL
seed="https://web.cs.dartmouth.edu/"

echo "Start crawling..."
./bin/crawler $seed
echo "Crawling done!"

echo "Building index"
./bin/indexer
echo "Index successfully built!"

./bin/engine
