/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:04:54 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 20:07:00 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	pathname = ft_strdup("/tmp/heredocm");
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

	fd = open(file, O_WRONLY | O_CREAT, 0644);
	write(fd, content, strlen(content));
	close(fd);
}

static void	heredoc_child(t_env *env, char *file, char *eof)
{
	char	*input;
	char	*content;
	char	*tmp;

	content = ft_strdup("");
	while (1)
	{
		input = readline("heredoc > ");
		if (!input || ft_strcmp(input, eof) == 0)
		{
			var_expand(env, &content);
			write_file(file, content);
			free(input);
			free(content);
			return ;
		}
		input = ft_strpush(&input, '\n');
		tmp = content;
		content = ft_strjoin(content, input);
		free(tmp);
		free(input);
	}
}

char	*heredoc_start(t_info *info, char *eof)
{
	char	*file;
	pid_t	pid;
	int		status;

	file = get_available_pathname();
	heredoc_sig();
	pid = fork();
	if (pid == 0)
	{
		heredoc_child(info->env, file, eof);
		free(file);
		free_info(info);
		close_std();
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	init_signals();
	if (WIFEXITED(status))
		g_err = WEXITSTATUS(status);
	if (access(file, F_OK) == 0)
		return (file);
	free(file);
	return (NULL);
}
