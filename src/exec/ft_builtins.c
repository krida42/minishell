/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:09:07 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/16 14:54:37 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_pwd(void)
{
	char	cwd[PATH_MAX + 1];
	int		fd;

	fd = 1;
	if (getcwd(cwd, sizeof(cwd)) != NULL) // return a null-terminated string containing an absolute pathname that is the current working directory of the calling process.
	{
		ft_putstr_fd(cwd, fd);
		ft_putstr_fd("\n", fd);
	}
	else
		perror("getcwd()");
	return (0);
}

static int ft_check_n(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-') //ft_strcmp(cmd->ag[i],"-n") == 0
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	else
		return (1);
}

int	ft_builtin_echo(t_cmd *cmd)
{
	int	i;
	int	j;
	
	i = 1;
	j = 0;
	if (cmd->ag[i])
	{
		while (ft_check_n(cmd->ag[i]) == 0)
		{
			j = 1;
			i++;
		}
		while (cmd->ag[i] != NULL)
		{
			ft_putstr_fd(cmd->ag[i], 1);
			if (cmd->ag[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if (j == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}

// int	ft_builtin_echo(t_cmd *cmd)
// {
// 	int	i;
// 	int	j;
// 	int	fd;
	
// 	i = 1;
// 	j = 0;
// 	while (ft_strcmp(cmd->ag[i],"-n") == 0) // revoit le parsing pour -nnnnnnnn
// 	{
// 		j = 1;
// 		i++;
// 	}
// 	fd = 1;
// 	while (cmd->ag[i])
// 	{
		
// 		ft_putstr_fd(cmd->ag[i], fd);
// 		if (cmd->ag[i + 1] != NULL)
// 			ft_putstr_fd(" ", fd);
// 		i++;
// 	}
// 	if (j == 0)
// 		ft_putstr_fd("\n", fd);
// 	return (0);
// }

// int	ft_builtin_cd(char *path)
// {
// 	if (chdir(path) != 0)
// 		perror("chdir() :");
// 	fprintf(stderr, "in cd paht is %s\n", path);
// 	return (0);
// }