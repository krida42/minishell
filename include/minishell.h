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
# include <limits.h>
# include <stddef.h>

# include <errno.h>

# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

extern int	g_err;

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
	int				status;
	int				error_n;
	pid_t			pid; // execution: pour fork
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
	int		error_n;
	t_env	*env;
}	t_info;

int		m_prompt(const char *prompt, char **envp);

char	*ft_strstr(const char *big, const char *little);
int		ft_strchri(const char *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strndup(const char *s, size_t n);
int		ft_isblank(char c);

int		strs_len(char **strs);
char	**strs_insert(char ***strs, const char *s);
char	**free_strs(char	**strs);
int		isinset(char c, const char *set);
char	**strs_remove(char ***strs, int index);

char	*skip_spaces(char *s);
int		skip_spaces_i(char *s);
void	ft_puterr(char *s, char *s1, char *s2);
char	*ft_strpush(char **s, char c); //faire gaffe

void	init_signals(void);
void	ignore_signals(void);
void	redefault_signals(void);

int		end_token_i(char *input);
int		set_redirect(t_cmd *cmd, char *cursor);

int		parse(char *input, t_info *info);
//
void	set_quote_state(char c, int *squote, int *dquote);
int		check_unclosed(char *input);
int		check_special(char *input);

int		is_cmd_err(t_info *info);

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
t_env	*env_dup(t_env *env);//no tested
void	free_env(t_env *env);
void	free_allenv(t_env *env);

t_info	*init_info(char **envp);
void	set_cmd(t_info *info, t_cmd *cmd);
void	reset_info(t_info *info);
void	free_info(t_info *info);

int		treat_allparam(t_env *env, t_cmd *cmd, t_info *info);
int		treat_allcmd(t_info *info);

void	var_expand(t_env *env, char **s);
int		clearify_allvar(t_cmd *cmd);
void	init_allvar(t_env **env, t_cmd *cmd);
int		is_varinit(char *s);
int		are_allvarinit(char **ag);
int		is_validid(char *s);// no tested

int		b_export(t_info *info, char **args);
int		b_env(t_info *info, char **args);
int		b_unset(t_info *info, char **args);

char	*heredoc_start(t_info *info, char *eof);
void	heredoc_handler(int sig);
void	heredoc_sig(void);

//  - - - - - - - - - - - - EXEC - - - - - - - - - - - - - - - - - -
//  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int		execute(t_info *info);
int		save_stdinout(int n);
int		dup_filefds(t_cmd *cmd);
int		dup_pipefds(t_cmd *cmd);
// char	*command_path(char **ag, t_info *info);
char	*command_path(char **ag, t_env *env);
void	ft_path(char **env, t_info *info);
// char	**path_tab(t_info *info);
char	**ft_split_pipex(char const *s, char c);
int		is_heredoc(char *heredoc, t_cmd *cmd, t_info *info); // to be deleted ?
int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, t_info *info);
int		ft_builtin_cd(char **ag, t_env *env);
int		ft_builtin_pwd(void);
int		ft_builtin_echo(t_cmd *cmd);
int		ft_builtin_exit(char **ag, t_info *info);
void	msg_close_free_exit(char *str, t_info *info); // p.e to be deleted
void	msg_close_return(char *str, t_info *info);
void	open_files(t_cmd *cmd);
// int		open_cmd_files(t_cmd *cmd, t_info *info);
int		open_pipes(t_cmd *cmd);
void	close_pipes(t_cmd *cmd);
void	close_files(t_cmd *cmd); //p.e to be deleted
void	close_cmd_files(t_cmd *cmd);
void	close_std(void);
void	close_pipes_files(t_cmd *cmd);//p.e to be deleted
void	close_pipes_cmdfiles(t_cmd *cmd);
int		msg_perror_return(char *str, int i);
void	ft_free(t_info *info); // a REVOIR Supprimer ?
void	ft_free_tab(char **tab); // a revoir

#endif
