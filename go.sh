#!/bin/bash

nasm -f elf64 test.s -o test.o
ld test.o -o test
./test
