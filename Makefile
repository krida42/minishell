.PHONY : all clean fclean re

CC := gcc
CFLAGS := -Wall -Werror -Wextra
SANI = -g -fsanitize=address -fsanitize=leak
INC_PATH := include/

PARSING_SRC := main.c prompt.c mini_utils.c signals.c \
			   parse.c check.c lst.c
EXEC_SRC := tes_fichiers.c

SRC := $(addprefix parsing/,$(PARSING_SRC))

OBJ := $(SRC:.c=.o)

SRC_PATH := src/
OBJ_PATH := obj/
SRC := $(addprefix $(SRC_PATH),$(SRC))
OBJ := $(addprefix $(OBJ_PATH),$(OBJ))
NAME := minishell


all : obj_dir $(NAME)

obj_dir :
	@mkdir -p obj
	@mkdir -p obj/parsing
	@mkdir -p obj/exec

$(NAME) : $(OBJ)
	$(CC) $^ -o minishell -Llibft -lft -lreadline $(SANI)

$(OBJ) : $(INC_PATH)color.h $(INC_PATH)minishell.h Makefile

lib :
	make -C libft

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -I$(INC_PATH) -c $< -o $@ $(SANI)

clean :
	rm -f $(OBJ)
	rm -rf obj/

fclean : clean
	rm -f $(NAME)

re : fclean all

test : all
	./minishell

