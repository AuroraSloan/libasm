NAME := libasm.a
CC := gcc
ASM := nasm
CFLAG := -Wall -Wextra -Werror -fpie -pie
ASMFLAG := -f elf64
SRC := $(wildcard *.s)
OBJ := $(SRC:.s=.o)
TEST := main.c

%.o: %.s
	$(ASM) $(ASMFLAG) $< -o $@

all :$(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

test: $(NAME)
	$(CC) $(CFLAG) $(TEST) $(NAME) -o test && ./test

clean-test:
	rm -rf test

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus test clean-test
