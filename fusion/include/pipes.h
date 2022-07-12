/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:07:07 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/11 17:57:32 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_cmd {
	char			**ag;
	char			*in;
	char			*out;
	char			*append;
	char			*heredoc;
	char			*cmd_path; // execution: pour execve
	int				pipefd[2]; // execution: pour pipe
	int				fdin; // execution: pour entrée
	int				fdout; // execution: pour sortie
	pid_t			pid; // execution: pour fork
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;
typedef struct s_info
{
	t_cmd	*cmd;
	int		size;
	char	**env;
	char	*path;
}			t_info;

void	execute(t_info *info);
char	*command_path(char **ag, t_info *info);
void	ft_path(char **env, t_info *info);
char	**path_tab(t_info *info);
char	**ft_split_pipex(char const *s, char c);
int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_cmd  *cmd, t_info *info);
int		ft_builtin_cd(char *path);
int		ft_builtin_pwd(void);
int		ft_builtin_echo(t_cmd *cmd);
void	msg_close_free_exit(char *str, t_info *info);
void	open_files(t_cmd *cmd);
void	open_pipes(t_cmd *cmd, t_info *info);
void	close_pipes(t_cmd *cmd);
void	close_files(t_cmd *cmd);
void	close_std(void);
void	ft_free(t_info *info);
void	ft_free_tab(char **tab);

//lib
int	ft_strcmp(char *s1, char *s2);
void	ft_putchar(char c);
void	ft_putstr(char *s);

// lst
t_cmd	*get_first(t_cmd *cmd); // no tested
t_cmd	*get_last(t_cmd *cmd); // no tested
void	add_back(t_cmd **cmd, char **ag);
int		cmd_size(t_cmd *cmd); // no tested
t_cmd	*new_cmd(char **ag); // static minishell

//to be deleted - not needed for minishell
t_info	*ft_init_info(char **envp);
void	ft_print_info(t_info *info);
t_cmd	*ft_arg_to_cmd(int ac, char **av, t_info *info);
void	ft_free(t_info *info);

#endif
