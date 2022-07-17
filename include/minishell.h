#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "color.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>

# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

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


typedef struct s_env {
	char			*name;
	char			*val;
	int				is_export;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_info {
	t_cmd	*cmd;
	int		size;
	t_env	*env;
}	t_info;

int		m_prompt(const char *prompt, char **envp);

char	*ft_strstr(const char *big, const char *little);
int		ft_strchri(const char *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strndup(const char *s, size_t n);

int		strs_len(char **strs);
char	**strs_insert(char ***strs, const char *s);
void	free_strs(char	**strs);
int		isinset(char c, const char *set);

char	*skip_spaces(char *s);
int		skip_spaces_i(char *s);

void	init_signals(void);

int		parse(char *input, char **envp);
//
void	set_quote_state(char c, int *squote, int *dquote);
int		check_unclosed(char *input);
int		check_special(char *input);

t_cmd	*get_first(t_cmd *cmd); // no tested
t_cmd	*get_last(t_cmd *cmd); // no tested
void	add_back(t_cmd **cmd, char **ag);
int		cmd_size(t_cmd *cmd);

void	free_cmd(t_cmd *cmd);
void	free_allcmd(t_cmd *cmd);

void	desc_token(char **strs);
void	desc_allcmd(t_cmd *cmd);
void	desc_info(t_info *info);


void	env_add(t_env **env, char *name, char *val, int is_export);
void	env_rm(t_env **env, char *name);
t_env	*env_get_ptr(t_env *env, char *name);
char	*env_get_val(t_env *env, char *name);
void	env_set_val(t_env *env, char *name, char *val);
void	env_set_export(t_env *env, char *name, int is_export);
t_env	*env_strs_toenv(char **strs_envp);
char	**env_env_tostrs(t_env *env);
void	free_env(t_env *env);
void	free_allenv(t_env *env);

t_info	*init_info(t_cmd *cmd, char **envp);
void	free_info(t_info *info);

//  - - - - - - - - - - - - EXEC - - - - - - - - - - - - - - - - - -
//  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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
void	ft_free(t_info *info); // a REVOIR Supprimer ?
void	ft_free_tab(char **tab); // a revoir

//lib
void	ft_putchar(char c);
void	ft_putstr(char *s);


#endif
