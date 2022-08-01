/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:09:07 by esmirnov          #+#    #+#             */
/*   Updated: 2022/08/01 14:11:19 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_pwd(void)
{
	char	cwd[PATH_MAX + 1];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		perror("pwd failed ");
		return (1);
	}
	return (0);
}

static int	ft_check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
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
	while (cmd->ag[i] && ft_check_n(cmd->ag[i]) == 0)
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
	if (j == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	ft_builtin_cd(char **ag, t_env *env)
{
	char	*tmp_pwd;

	if (ag[1] != NULL && ag[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (ag[1] == NULL)
	{
		tmp_pwd = env_get_val(env, "HOME");
		if (chdir (tmp_pwd) == -1)
		{
			free (tmp_pwd);
			return (msg_perror_return("cd: failed ", 1));
		}
		free (tmp_pwd);
	}
	else if (chdir (ag[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		return (msg_perror_return(ag[1], 1));
	}
	tmp_pwd = getenv("PWD");
	env_set_val(env, "PWD", tmp_pwd);
	return (0);
}
