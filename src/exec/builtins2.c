/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:27:30 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/27 15:49:08 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] <'0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_builtin_exit(char **ag, t_info *info)
{
	if (ag[1] != NULL && is_num(ag[1]) == 0)
	{
		printf("%s: %s: numeric argument required\n", ag[0], ag[1]);
		return ;
	}
	else if (ag[1] != NULL && ag[2] != NULL)
	{
		printf("%s: too many arguments\n", ag[0]);
		return ;
	}
	else if (ag[1] != NULL)
	{
		// ft_putstr_fd("exit\n", 1);
		info->error_n = ft_atoi(ag[1]) % 256;
	}
	// else if (cmd->out == NULL)
	// 	ft_putstr_fd("exit\n", 1);
	return ;
}