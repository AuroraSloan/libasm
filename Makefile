.PHONY: all debug leakcheck bonus clean fclean re

NAME := libasm.a

ASM := nasm
ASMFLAG := -f elf64
ASM_SRC := $(wildcard *.s)
ASM_OBJ := $(ASM_SRC:.s=.o)

CC := gcc
CFLAG := -Wall -Wextra -Werror -fpie -pie
SRC := main.c
OBJ := $(SRC:.c=.o)
SRC_B := main_bonus.c
OBJ_B := $(SRC_B:.c=.o)

LIBASM_TEST := libasm_test
LIBASM_TEST_B := libasm_test_b

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

$(LIBASM_TEST_B): $(NAME) $(OBJ_B)
	$(CC) $(CFLAG) $(OBJ_B) $(NAME) -o $(LIBASM_TEST_B)

debug: fclean
	$(MAKE) DEBUG=1 SANITIZE=1 all
	./$(LIBASM_TEST)

leakcheck: fclean
	$(MAKE) DEBUG=1 all
	valgrind --leak-check=full -s ./$(LIBASM_TEST)

bonus:
	$(MAKE) DEBUG=1 $(LIBASM_TEST_B)
	./$(LIBASM_TEST_B)

clean:
	rm -rf $(ASM_OBJ) $(OBJ) $(OBJ_B)

fclean: clean
	rm -rf $(NAME) $(LIBASM_TEST) $(LIBASM_TEST_B)

re: fclean all
