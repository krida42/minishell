# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 13:37:32 by esmirnov          #+#    #+#              #
#    Updated: 2022/07/06 14:09:55 by esmirnov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	execute

SRCS		=	$(addprefix src/,\
				main.c\
				execute.c\
				command_path.c\
				ft_split_pipex.c\
				exec_builtin.c\
				ft_builtins.c\
				open.c\
				close.c\
				free.c\
				msg_close_free_exit.c\
				utils_exec.c\
				lst.c\
				ft_init_info.c\
				ft_arg_to_cmd.c\
				ft_print_info.c)

OBJS		=	$(SRCS:src/%.c=objects/%.o)

DEP			=	$(SRCS:src/%.c=objects/%.d)

CFLAGS		=	-Wall -Werror -Wextra -MMD -g3 -O3

CC			=	gcc

INC			=	-Iinclude -Ilibft

LIBFT		=	libft/libft.a

RM			=	rm -rf

# -p if directory exists very is no warning etc
objects/%.o:	src/%.c
	mkdir -p objects
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(INC) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	@make -C libft/
	
#delete .o files
clean: libft_clean
	$(RM) $(DEP) $(OBJS) objects

libft_clean:
	make clean -C libft/
	
fclean:	clean
	$(RM) $(NAME)

# delete all and recompile all
re:	fclean
	make all

-include $(DEP)

.PHONY:	all clean libft_clean fclean re
