CC := gcc
CFLAGS := -Wall -Wextra -Werror
SANI2 := -g -fsanitize=address -fsanitize=leak
SANI := -g
INC_PATH := include/
SHELL = /bin/bash

PARSING_SRC := main.c prompt.c lib_utils.c signals.c \
			   parse.c check.c lst.c lst2.c utils.c utils2.c desc.c \
			   env.c env2.c env3.c info.c expand.c expand2.c var.c \
			   b_export.c b_env.c b_unset.c heredoc.c check2.c redirect.c \
			   expand0.c parse0.c heredoc2.c

EXEC_SRC :=  	execute.c		\
				exec_fds.c		\
				command_path.c	\
				ft_split_pipex.c\
				builtin_exec.c	\
				builtins.c		\
				builtins2.c		\
				open.c			\
				close.c			\
				msg.c			\
				free.c

SRC := $(addprefix parsing/,$(PARSING_SRC))
SRC += $(addprefix exec/,$(EXEC_SRC))

OBJ := $(SRC:.c=.o)

SRC_PATH := src/
OBJ_PATH := obj/
SRC := $(addprefix $(SRC_PATH),$(SRC))
OBJ := $(addprefix $(OBJ_PATH),$(OBJ))
NAME := minishell


ERROR_COLOR = \033[0;31m
WARN_COLOR = \033[0;33m
NO_COLOR = \033[m

BLUE_COLOR = \033[1;34m
CYAN_COLOR = \033[1;36m
GREEN_COLOR = \033[1;32m
PURPLE_COLOR = \033[1;35m
GRAY_COLOR = \033[0;37m
DGRAY_COLOR = \033[1;30m
WHITE_COLOR = \033[1;37m

all : lib obj_dir $(NAME)

obj_dir :
	@mkdir -p obj
	@mkdir -p obj/parsing
	@mkdir -p obj/exec

$(NAME) : $(OBJ)
	@$(CC) $^ -o minishell -Llibft -lft -lreadline $(SANI)
	@echo "| - - - - - - - - - |"
	@echo -e "| $(CYAN_COLOR)Compilation done!$(NO_COLOR) |"
	@echo "| - - - - - - - - - |"
	

$(OBJ) : $(INC_PATH)color.h $(INC_PATH)minishell.h Makefile

lib :
	@make -C libft

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -I$(INC_PATH) -c $< -o $@ $(SANI)

clean :
	@rm -f $(OBJ)
	@rm -rf obj/
	@echo -e "| $(PURPLE_COLOR)Objects cleaned$(NO_COLOR)   |"

fclean : clean
	@rm -f $(NAME)
	@echo -e "| $(PURPLE_COLOR)Exec cleaned$(NO_COLOR)	    |"

re : fclean all

test : all
	@echo 
	@./minishell

fsan_def :
	$(eval SANI := -g -fsanitize=address -fsanitize=leak)

san : fsan_def test

.PHONY : all clean fclean re test fsan_def san
