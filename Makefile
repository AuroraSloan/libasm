.PHONY: all debug leakcheck clean fclean re

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
	CFLAG += -g -O0
endif

ifdef SANITIZE
	CFLAG += -fsanitize=address
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

debug: fclean
	$(MAKE) DEBUG=1 SANITIZE=1 all
	./$(LIBASM_TEST)

leakcheck: fclean
	@$(MAKE) DEBUG=1 all
	valgrind --leak-check=full -s ./$(LIBASM_TEST)

clean:
	rm -rf $(ASM_OBJ) $(OBJ)

fclean: clean
	rm -rf $(NAME) $(LIBASM_TEST)

re: fclean all
