#!/bin/bash

nasm -f elf64 write_string.s -o write_string.o
gcc -fpie -pie main.c write_string.o -o test
./test
