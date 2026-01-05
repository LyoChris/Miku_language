#!/usr/bin/env bash
set -euo pipefail

# convert CRLF -> LF if dos2unix exists
if command -v dos2unix >/dev/null 2>&1; then
  dos2unix miku.l miku.y >/dev/null 2>&1 || true
fi

rm -f miku.tab.* miku.yy.* lex.yy.* y.tab.* miku

bison -d -o miku.tab.cpp --defines=miku.tab.hpp miku.y
flex  -o miku.yy.cpp miku.l

g++ -std=c++17 -O2 -Wall -Wextra -o miku \
  miku_impl.cpp miku.tab.cpp miku.yy.cpp
