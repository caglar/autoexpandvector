#!/bin/bash
gcc -std=c99 -pedantic -Wall -O3 -c autoexpandvector.c autoexpandvector.h 
gcc -std=c99 -Wall autoexpandvector.o test.c -o test
rm *.o
