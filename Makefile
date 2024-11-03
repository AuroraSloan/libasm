.PHONY: all debug leakcheck bonus clean fclean re

NAME := libasm.a
NAME_B := libasm_bonus.a

ASM := nasm
ASMFLAG := -f elf64
ASM_SRC := $(wildcard *.s)
ASM_OBJ := $(ASM_SRC:.s=.o)
ASM_SRC_B := $(wildcard bonus/*.s)
ASM_OBJ_B := $(ASM_SRC_B:.s=.o)

CC := gcc
CFLAG := -Wall -Wextra -Werror -fpie -pie
SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
SRC_B := $(wildcard bonus/*.c)
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

$(NAME_B): $(ASM_OBJ_B)
	ar rc $(NAME_B) $(ASM_OBJ_B)
	ranlib $(NAME_B)

$(LIBASM_TEST_B): $(NAME_B) $(OBJ_B)
	$(CC) $(CFLAG) $(OBJ_B) $(NAME_B) -o $(LIBASM_TEST_B)

debug: fclean
	$(MAKE) DEBUG=1 SANITIZE=1 all
	./$(LIBASM_TEST)

leakcheck: fclean
	@$(MAKE) DEBUG=1 all
	valgrind --leak-check=full -s ./$(LIBASM_TEST)

bonus: fclean
	$(MAKE) DEBUG=1 $(LIBASM_TEST_B)
	./$(LIBASM_TEST_B)

clean:
	rm -rf $(ASM_OBJ) $(OBJ)
	rm -rf $(ASM_OBJ_B) $(OBJ_B)

fclean: clean
	rm -rf $(NAME) $(LIBASM_TEST)
	rm -rf $(NAME_B) $(LIBASM_TEST_B)

re: fclean all
