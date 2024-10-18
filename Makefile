NAME := libasm.a

ASM := nasm
ASMFLAG := -f elf64
ASM_SRC := $(wildcard *.s)
ASM_OBJ := $(ASM_SRC:.s=.o)

CC := gcc
CFLAG := -Wall -Wextra -Werror -fpie -pie
SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)

LIBASM_TEST := libasm_test

ifdef DEBUG
	CFLAG += -g -o0
endif

%.o: %.s
	$(ASM) $(ASMFLAG) $< -o $@

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

all: $(LIBASM_TEST)

$(NAME): $(ASM_OBJ)
	ar rc $(NAME) $(ASM_OBJ)
	ranlib $(NAME)

$(LIBASM_TEST): $(NAME) $(OBJ)
	$(CC) $(CFLAG) $(OBJ) $(NAME) -o $(LIBASM_TEST)

test-mem:
	make fclean
	make DEBUG=1
	valgrind --leak-check=full -s ./$(LIBASM_TEST)

clean:
	rm -rf $(ASM_OBJ) $(OBJ)

fclean: clean
	rm -rf $(NAME) $(LIBASM_TEST)

re: fclean all

.PHONY: all test-mem clean fclean re
