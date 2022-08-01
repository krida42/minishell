/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:59:35 by esmirnov          #+#    #+#             */
/*   Updated: 2022/08/01 23:03:47 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_av_cmd_error_msg_check(char **ag)
{
	if (ft_strchr(ag[0], '/') != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(ag[0]);
	}
	else
	{
		ft_putstr_fd(ag[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_err = 127;
	}
	return ;
}

static char	**path_tab(t_env *env)
{
	char	*path_tmp;
	char	**pathtab;
	int		i;

	pathtab = NULL;
	path_tmp = env_get_val(env, "PATH");
	if (!path_tmp)
		path_tmp = env_get_val(env, "PWD");
	if (path_tmp != NULL)
	{
		pathtab = ft_split_pipex((char const *)path_tmp, ':');
		free(path_tmp);
		i = 0;
		while (pathtab[i])
		{
			if (pathtab[i][0] != '\0')
			{
				path_tmp = ft_strjoin(pathtab[i], "/");
				free (pathtab[i]);
				pathtab[i] = path_tmp;
			}
			i++;
		}
	}
	return (pathtab);
}

static int	is_dir(char *ag)
{
	int	fd;

	fd = open(ag, O_DIRECTORY);
	if (fd != -1)
	{
		close (fd);
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd(ag, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		g_err = 126;
		return (1);
	}
	return (0);
}

static int	check_access(char *pathname, char **pathtab, int mode)
{
	if (access(pathname, mode) == 0 && ft_strchr(pathname, '/') != NULL)
	{
		ft_free_tab(pathtab);
		return (1);
	}
	return (0);
}

char	*command_path(char **ag, t_env *env)
{
	char	*cmd_path;
	char	**pathtab;
	int		i;

	if (is_dir(ag[0]) == 1)
		return (NULL);
	pathtab = path_tab(env);
	if (pathtab != NULL)
	{
		i = 0;
		while (pathtab[i])
		{
			cmd_path = ft_strjoin(pathtab[i], ag[0]);
			if (check_access(cmd_path, pathtab, F_OK) == 1)
				return (cmd_path);
			free(cmd_path);
			i++;
		}
	}
	if (check_access(ag[0], pathtab, X_OK) == 1)
		return (ag[0]);
	ft_free_tab(pathtab);
	ft_av_cmd_error_msg_check(ag);
	return (NULL);
}
