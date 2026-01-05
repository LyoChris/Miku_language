#!/bin/bash

# Clean up old files
rm -f miku miku.tab.c lex.yy.c miku.tab.h tables.txt

# Generate the Parser
bison -d -Wcounterexamples miku.y

# Generate the Lexer
flex miku.l

# Compile everything using g++ 
# REMOVED -lfl because we define our own main and use %option noyywrap
g++ -o miku miku.tab.c lex.yy.c miku_impl.cpp