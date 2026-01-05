#!/bin/bash

# Clean up old files
rm -f miku miku.tab.c lex.yy.c miku.tab.h

# Generate the Parser (C++ compatible C code)
bison -d -Wcounterexamples miku.y

# Generate the Lexer
flex miku.l

# Compile everything using g++ 
# We add 'miku_impl.cpp' which contains the SymbolTable and AST logic
g++ -o miku miku.tab.c lex.yy.c miku_impl.cpp -lfl