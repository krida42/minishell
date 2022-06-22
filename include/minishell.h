#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "color.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>

# define LITERAL 42
# define PIPE 7
# define REDIRECTION 18

typedef int	t_toktype;

typedef struct s_token {
	char			*value;
	t_toktype		type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

int		m_prompt(const char *prompt);

char	*ft_strstr(const char *big, const char *little);
int		ft_strchri(const char *s, char c);

void	init_signals(void);

int		parse(char *input);
int		check_unclosed(char *input);
int		check_special(char *input);


t_token	*get_first(t_token *token); // no tested
t_token	*get_last(t_token *token); // no tested
void	add_back(t_token **token, char *value, t_toktype type); //no teste
int		token_size(t_token *token); // no tested
#endif
