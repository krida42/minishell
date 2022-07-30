/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:59:35 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/30 19:43:43 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	ft_av_cmd_error_msg_check(char **ag, t_info *info) 
static void	ft_av_cmd_error_msg_check(char **ag) // a voir s il est possble faire differement
{
	if (ft_strchr(ag[0], '/') != NULL)
		perror(ag[0]);
	else 
	{
		ft_putstr_fd(ag[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_err = 127;
	}
	// close_pipes(info->cmd);
	// close_files(info->cmd);
	// exit(EXIT_FAILURE);
	return ;
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

// static char	**path_tab(t_info *info)
static char	**path_tab(t_env *env)
{
	char	*path_tmp;
	char	**pathtab;
	int		i;

	// ft_path(info->env, info);
	pathtab = NULL;
	// path_tmp = info->path;
	path_tmp = env_get_val(env, "PATH");
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

// static int check_access(char *path, char *ag)
// {
// 	int	fd;

// 	if (access(path, F_OK) == 0 && ft_strchr(path, '/') != NULL)
// 	{
// 		fd = open(path, O_DIRECTORY);
// 		if (fd != -1)
// 		{
// 			ft_putstr_fd(ag, 2);
// 			ft_putstr_fd(": Is a directory\n", 2);
// 			return (1);
// 		}
// 		close (fd);
// 	}
// 	return (0);
// }

static int	is_dir(char *ag)
{
	int	fd;
	
	fd = open(ag, O_DIRECTORY | O_CLOEXEC);
	if (fd != -1)
	{
		close (fd);
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

// char	*command_path(char **ag, t_info *info)
char	*command_path(char **ag, t_env *env)
{
	char	*cmd_path;
	char	**pathtab; // to do dans info?
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
	ft_av_cmd_error_msg_check(ag); // a voir s il est possible differement
	return (NULL);
}

/*reserve 0729_01*/
// char	*command_path(char **ag, t_env *env)
// {
// 	char	*cmd_path;
// 	char	**pathtab; // to do dans info?
// 	int		i;
// 	// int		fd;

// 	if (is_dir(ag[0]) == 1)
// 		return (NULL);
// 	pathtab = path_tab(env);
// 	if (pathtab != NULL)
// 	{
// 		i = 0;
// 		while (pathtab[i])
// 		{
// 			cmd_path = ft_strjoin(pathtab[i], ag[0]);
// 			if (check_access(cmd_path, pathtab, F_OK) == 1)
// 				return (cmd_path);
// 			// if (access(cmd_path, F_OK) == 0 && ft_strchr(cmd_path, '/') != NULL)
// 			// {
// 			// 	ft_free_tab(pathtab);
// 			// 	return (cmd_path);
// 			// }
// 			free(cmd_path);
// 			i++;
// 		}
// 	}
// 	if (check_access(ag[0], pathtab, X_OK) == 1)
// 		return (ag[0]);
// 	// if (access(ag[0], X_OK) == 0 && ft_strchr(ag[0], '/') != NULL)
// 	// {
// 	// 	ft_free_tab(pathtab);
// 	// 	return (ag[0]);
// 	// }
// 	ft_free_tab(pathtab);
// 	ft_av_cmd_error_msg_check(ag); // a voir s il est possible differement
// 	return (NULL);
// }

/*reserve 07_29*/
// char	*command_path(char **ag, t_info *info)
// char	*command_path(char **ag, t_env *env)
// {
// 	char	*cmd_path;
// 	char	**pathtab; // to do dans info?
// 	int		i;
// 	// int		fd;

// 	if (is_dir(ag[0]) == 1)
// 		return (NULL);
// 	pathtab = path_tab(env);
// 	if (pathtab != NULL)
// 	{
// 		i = 0;
// 		while (pathtab[i])
// 		{
// 			cmd_path = ft_strjoin(pathtab[i], ag[0]);
// 			// if (check_access(cmd_path, ag[0]) == 1)
// 			// 	return (cmd_path);
// 			if (access(cmd_path, F_OK) == 0 && ft_strchr(cmd_path, '/') != NULL)
// 			{
// 				// fd = open(cmd_path, O_DIRECTORY);
// 				// if (fd != -1)
// 				// {
// 				// 	close (fd);
// 				// ft_free_tab(pathtab);
// 				// 	ft_putstr_fd(ag[0], 2);
// 				// 	ft_putstr_fd(": Is a directory\n", 2);
// 				// 	return (NULL);
// 				// }
// 				ft_free_tab(pathtab);
// 				return (cmd_path);
// 			}
// 			free(cmd_path);
// 			i++;
// 		}
// 	}
// 	// if (check_access(ag[0], ag[0], pathtab) == 1)
// 	// 	return (ag[0]);
// 	if (access(ag[0], X_OK) == 0 && ft_strchr(ag[0], '/') != NULL)
// 	{
// 		// fd = open(ag[0], O_DIRECTORY);
// 		// if (fd != -1)
// 		// {
// 		// 	close (fd);
// 		// 	ft_free_tab(pathtab);
// 		// 	ft_putstr_fd(ag[0], 2);
// 		// 	ft_putstr_fd(": Is a directory\n", 2);
// 		// 	return (NULL);
// 		ft_free_tab(pathtab);
// 		return (ag[0]);
// 	}
// 	ft_free_tab(pathtab);
// 	ft_av_cmd_error_msg_check(ag); // a voir s il est possible differement
// 	return (NULL);
// }

/*reserve 07_29 - 00*/
// char	*command_path(char **ag, t_info *info)
// char	*command_path(char **ag, t_env *env)
// {
// 	char	*cmd_path;
// 	char	**pathtab; // to do dans info?
// 	int		i;

// 	pathtab = path_tab(env);
// 	if (pathtab != NULL)
// 	{
// 		i = 0;
// 		while (pathtab[i])
// 		{
// 			cmd_path = ft_strjoin(pathtab[i], ag[0]);
// 			if (access(cmd_path, F_OK) == 0 && ft_strchr(cmd_path, '/') != NULL)
// 				return (cmd_path);
// 			free(cmd_path);
// 			i++;
// 		}
// 	}
// 	if (access(ag[0], X_OK) == 0
// 		&& ft_strchr(ag[0], '/') != NULL)
// 		return (ag[0]);
// 	ft_free_tab(pathtab);
// 	ft_av_cmd_error_msg_check(ag); // a voir s il est possible differement
// 	return (NULL);
// }