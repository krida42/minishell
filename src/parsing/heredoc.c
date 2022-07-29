#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*join_name_nb(char *name, int nb)
{
	char	*nb_s;
	char	*joined;

	nb_s = ft_itoa(nb);
	joined = ft_strjoin(name, nb_s);
	free(nb_s);
	return (joined);
}

static char	*get_available_pathname(void)
{
	char	*pathname;
	int		i;

	pathname = strdup("/tmp/heredocm");
	i = 0;
	while (access(pathname, F_OK) == 0)
	{
		free(pathname);
		pathname = join_name_nb("/tmp/heredocm_", i);
		i++;
	}
	return (pathname);
}

static void	write_file(char *file, char *content)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT,  0644);
	write(fd, content, strlen(content));
	close(fd);
}

static void	heredoc_child(t_env *env, char *file, char *eof, int err)
{
	char	*input;
	char	*content;
	char	*tmp;

	content = strdup("");
	while (1)
	{
		input = readline("heredoc > ");
		if (!input || strcmp(input, eof) == 0)
		{
			var_expand(env, &content, err);
			write_file(file, content);
			free(input);
			free(content);
			//return (file);
			return ;
		}
		input = ft_strpush(&input, '\n');
		tmp = content;
		content = ft_strjoin(content, input);
		free(tmp);
		free(input);
	}

}

static void	heredoc_handler(int sig)
{
	(void)sig;

	if (sig == SIGINT)
	{
		write(1, "\n", 2);
		exit(130);
	}

}
static void	heredoc_sig(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler= heredoc_handler;
	sigaction(SIGINT, &sa, NULL);
}

char	*heredoc_start(t_info *info, char *eof)
{
	char	*file;
	pid_t	pid;
	int	status;

	file = get_available_pathname();
	heredoc_sig();
	pid = fork();
	if (pid == 0)
	{

		heredoc_child(info->env, file, eof, info->error_n);
		free(file);
		free_info(info);
		exit(0);
	}
	init_signals();
	waitpid(pid, &status, 0);
	if (access(file, F_OK) == 0)
		return (file);
	free(file);
	return (NULL);
}
