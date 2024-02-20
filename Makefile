
#####################################
NAME = mrush
VPATH = src
#####################################
CC = gcc
CFLAGS = -Wall -Werror -Wextra
TEMP_FILE = .flag
#####################################
SRC=	mineria.c	\
		pow.c		\
		main.c		\
		error.c
OBJ_FOLDER = obj
OBJ = $(SRC:%.c=$(OBJ_FOLDER)/%.o)
#####################################
YELLOW		=		\033[93;1m
DARK_YELLOW	=		\033[0;33m
GREEN		=		\033[92;1m
DARK_GREEN	=		\033[0;32m
BLUE		=		\033[94;1m
CYAN		=		\033[96;1m
CLEAR		=		\033[0m
#####################################
#####################################
#####################################

# Default call
all: $(NAME)

# Compile the executable. Before, all the objects must be compiled/created
$(NAME): $(OBJ)
	@make -s clean_tmpfile
	@echo "$(DARK_YELLOW)[EXE] Compiling $(YELLOW)$(NAME)$(CLEAR)"
	@$(CC) $(OBJ) -o $(NAME) -pthread
	@echo "\n\t$(BLUE)Program compiled!. Usage: $(CYAN)./$(NAME) <TARGET_INI> <ROUNDS> <N_THREADS>$(CLEAR)\n"

# Compile all the necessary objects
$(OBJ_FOLDER)/%.o: %.c
	@if [ ! -e $(TEMP_FILE) ]; then \
		touch $(TEMP_FILE); \
		echo "$(DARK_GREEN)[OBJ] Compiling the objects$(CLEAR)"; \
	fi

	@echo "\t$(GREEN)=> Compiling $^$(CLEAR)"
	@mkdir -p $(OBJ_FOLDER)
	@$(CC) $(CFLAGS) -c $^ -o $@

clean_tmpfile:
	@rm -rf $(TEMP_FILE)
#####################################

clean:
	@rm -rf $(OBJ_FOLDER)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re clean_tmpfile clear r run

#####################################

clear:
	@clear

r:run1
rr: run1 run2
run1: clear all
	@valgrind --leak-check=full ./$(NAME) 0 5 3

run2: clear all
	@valgrind --leak-check=full ./$(NAME) 50 3 10