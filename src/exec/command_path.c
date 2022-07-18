/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:59:35 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/18 22:00:10 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_av_cmd_error_msg_check(char **ag, t_info *info) // a voir s il est possble faire differement
{
	if (ft_strchr(ag[0], '/') != NULL)
		perror(ag[0]);
	else
	{
		ft_putstr_fd(ag[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	close_pipes(info->cmd);
	close_files(info->cmd);
	exit(EXIT_FAILURE);
}


// void	ft_path(char **env, t_info *info)
// {
// 	if (*env)
// 	{
// 		while (env)
// 		{
// 			if (ft_strncmp(*env, "PATH=", 5) == 0)
// 				break ;
// 			env++;
// 		}
// 		info->path = *env + 5;
// 	}
// }

char	**path_tab(t_info *info)
{
	char	*path_tmp;
	char	**pathtab;
	int		i;

	// ft_path(info->env, info);
	pathtab = NULL;
	// path_tmp = info->path;
	path_tmp = env_get_val(info->env, "PATH");
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
	// free (path_tmp);
	return (pathtab);
}

char	*command_path(char **ag, t_info *info)
{
	char	*cmd_path;
	char	**pathtab; // to do dans info?
	int		i;

	pathtab = path_tab(info);
	if (pathtab != NULL)
	{
		i = 0;
		while (pathtab[i])
		{
			cmd_path = ft_strjoin(pathtab[i], ag[0]);
			if (access(cmd_path, F_OK) == 0 && ft_strchr(cmd_path, '/') != NULL)
				return (cmd_path);
			free(cmd_path);
			i++;
		}
	}
	if (access(ag[0], X_OK) == 0
		&& ft_strchr(ag[0], '/') != NULL)
		return (ag[0]);
	ft_free_tab(pathtab);
	ft_av_cmd_error_msg_check(ag, info); // a voir s il est possible differement
	return (NULL);
}
