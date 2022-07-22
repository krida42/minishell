/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:27:30 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/22 18:23:00 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] <'0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_builtin_exit(char **ag, t_cmd *cmd)
{
	ft_putstr_fd("exit\n", 1);
	if (ag[2])
	{
		ft_putstr_fd(ag[0], 1);
		ft_putstr_fd(": too many arguments\n", 1);
		return ;
	}
	else if (ag[1])
	{
		if (is_int(ag[1]) == 0)
		{
			ft_putstr_fd(ag[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			return ;
		}
		else
			cmd->error_n = ft_atoi(ag[1]) % 256;
	}
	return ;
}