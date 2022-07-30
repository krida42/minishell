/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:27:30 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/30 19:33:42 by esmirnov         ###   ########.fr       */
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

int	ft_builtin_exit(char **ag, t_info *info)
{
	(void)info;
	printf("exit\n");
	if (ag[1] != NULL && is_num(ag[1]) == 0)
	{
		printf("%s: %s: numeric argument required\n", ag[0], ag[1]);
		g_err = 2;
	}
	else if (ag[1] != NULL && ag[2] != NULL)
	{
		printf("%s: too many arguments\n", ag[0]);
		return (1);
	}
	else if (ag[1] != NULL)
	{
		// ft_putstr_fd("exit\n", 1);
		g_err = ft_atoi(ag[1]) % 256;
		fprintf(stderr,"g_err after ft_atoi is %d\n", g_err);
	}
	else
		g_err = 0;
	fprintf(stderr,"builtin EXIT g_err after free before exit is %d\n", g_err);
	free_info(info);
	save_stdinout(2);
	close_std();
	exit (g_err);
	// else if (cmd->out == NULL)
	// 	ft_putstr_fd("exit\n", 1);
}