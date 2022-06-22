#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "color.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>

# define CMD_AG 0
# define CMD_IN 1
# define CMD_OUT 2
# define CMD_APPEND 3
# define CMD_HEREDOC 4

typedef struct s_cmd {
	char			*ag;
	char			*in;
	char			*out;
	char			*append;
	char			*heredoc;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_info {
	t_cmd	*cmd;
	int		size;
	char	**env;
}	t_info;

int		m_prompt(const char *prompt);

char	*ft_strstr(const char *big, const char *little);
int		ft_strchri(const char *s, char c);

void	init_signals(void);

int		parse(char *input);
int		check_unclosed(char *input);
int		check_special(char *input);

t_cmd	*get_first(t_cmd *cmd); // no tested
t_cmd	*get_last(t_cmd *cmd); // no tested
void	add_back(t_cmd **cmd, char *properties[]); //no teste
int		cmd_size(t_cmd *cmd); // no tested
#endif
