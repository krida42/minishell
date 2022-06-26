#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "color.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>

typedef struct s_cmd {
	char	**ag;
	char	*in;
	char	*out;
	char	*append;
	char	*heredoc;
	char	*cmd_path; // execution: pour execve
	int		pipefd[2]; // execution: pour pipe
	int		fdin; // execution: pour entrée
	int		fdout; // execution: pour sortie
	pid_t	pid; // execution: pour fork
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_info {
	t_cmd	*cmd;
	int		size;
	char	**env;
	char	*path;
}	t_info;

int		m_prompt(const char *prompt);

char	*ft_strstr(const char *big, const char *little);
int		ft_strchri(const char *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strndup(const char *s, size_t n);

int		strs_len(char **strs);
char	**strs_insert(char ***strs, const char *s); 

void	init_signals(void);

int		parse(char *input);
int		check_unclosed(char *input);
int		check_special(char *input);

t_cmd	*get_first(t_cmd *cmd); // no tested
t_cmd	*get_last(t_cmd *cmd); // no tested
void	add_back(t_cmd **cmd, char **ag); //no teste
int		cmd_size(t_cmd *cmd); // no tested

void	desc_token(char **strs);
#endif
