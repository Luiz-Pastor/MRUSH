#####################################
NAME = mrush
#####################################
CC = gcc
CFLAGS = -Wall -Werror -Wextra
#####################################
SRC_FOLDER=src
SRC=	mineria.c	\
		pow.c

OBJ_FOLDER = obj
OBJ = $(SRC:%.c=$(OBJ_FOLDER)/%.o)
#####################################

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $< -o $(NAME) -pthread

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@mkdir -p $(OBJ_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@

#####################################

clean:
	@rm -rf $(OBJ_FOLDER)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re