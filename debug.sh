#!/bin/bash

nasm -f elf64 -g ft_strlen.s -o ft_strlen.o
nasm -f elf64 -g ft_strcpy.s -o ft_strcpy.o
nasm -f elf64 -g ft_strcmp.s -o ft_strcmp.o
nasm -f elf64 -g ft_write.s -o ft_write.o
nasm -f elf64 -g ft_read.s -o ft_read.o
nasm -f elf64 -g ft_strdup.s -o ft_strdup.o
gcc -Wall -Wextra -Werror -fpie -pie main.c ft_strlen.o ft_strcpy.o ft_strcmp.o ft_write.o ft_read.o ft_strdup.o
gdb ./a.out
