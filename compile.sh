#!/bin/bash
rm -f miku miku.tab.c lex.yy.c miku.tab.h

bison -d -Wcounterexamples miku.y
flex miku.l
gcc -o miku miku.tab.c lex.yy.c -lfl