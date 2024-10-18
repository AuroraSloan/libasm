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
	CFLAG += -fsanitize=address -g -o0
endif

ifdef LEAKCHECK
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

debug:
	make fclean
	make DEBUG=1
	./$(LIBASM_TEST)	

leakcheck:
	make fclean
	make LEAKCHECK=1
	valgrind --leak-check=full -s ./$(LIBASM_TEST)

clean:
	rm -rf $(ASM_OBJ) $(OBJ)

fclean: clean
	rm -rf $(NAME) $(LIBASM_TEST)

re: fclean all

.PHONY: all debug leakcheck clean fclean re
