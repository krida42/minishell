/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:26:26 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/31 20:03:22 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long int	ft_atoi_llong_int(const char *str)
{
	int				i;
	long long int	sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[0] == '\0')
	{
		perror("empty argument not valid: ");
		g_err = 1;
		exit(g_err);
	}
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str [i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str [i] <= '9')
		result = result * 10 + (str[i++] - '0');
	return (result * sign);
}

static int	check_long_int(char *str)
{
	int		n;
	char	*limit;

	n = 0;
	if (str[0] == '-')
		limit = "-9223372036854775808";
	else
	{
		if (str[0] == '+')
			n = 1;
		limit = "9223372036854775807";
	}
	while (str[n])
	{
		if (str[n] > limit[n])
			return (0);
		n++;
	}
	return (1);
}

static int	is_num(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		j = 1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i - j > 19)
		return (0);
	else if (i - j == 19 && check_long_int(str) == 0)
		return (0);
	return (1);
}

int	ft_builtin_exit(char **ag, t_info *info)
{
	printf("exit\n");
	if (ag[1] != NULL && is_num(ag[1]) == 0)
	{
		ft_putstr_fd("minishell: ", 1);
		printf("%s: %s: numeric argument required\n", ag[0], ag[1]);
		g_err = 2;
	}
	else if (ag[1] != NULL && ag[2] != NULL)
	{
		ft_putstr_fd("minishell: ", 1);
		printf("%s: too many arguments\n", ag[0]);
		return (1);
	}
	else if (ag[1] != NULL)
		g_err = (int)ft_atoi_llong_int(ag[1]) % 256;
	else
		g_err = 0;
	free_info(info);
	save_stdinout(2);
	close_std();
	exit (g_err);
}
