/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:59:39 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 19:59:40 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int	is_validid(char *s)
{
	while (*s)
	{
		if (!(ft_isalnum(*s) || *s == '_'))
			return (0);
		s++;
	}
	return (1);
}

int	is_varinit(char *s)
{
	if (*s == '=')
		return (0);
	while (*s)
	{
		if (!(ft_isalnum(*s) || *s == '_'))
			break ;
		s++;
	}
	if (*s == '=')
		return (1);
	return (0);
}

int	are_allvarinit(char **ag)
{
	while (*ag)
	{
		if (!is_varinit(*ag))
			return (0);
		ag++;
	}
	return (1);
}

int	clearify_allvar(t_cmd *cmd)
{
	char	**ag;
	int		i;

	ag = cmd->ag;
	i = -1;
	if (!ag)
		return (1);
	if (!are_allvarinit(ag) || cmd->next || cmd->prev)
	{
		while (ag[++i])
		{
			if (!is_varinit(ag[i]))
				break ;
			strs_remove(&ag, i);
			i = -1;
		}
	}
	else
		return (0);
	if (!ag[0])
		ag = free_strs(ag);
	cmd->ag = ag;
	return (1);
}

void	init_allvar(t_env **env, t_cmd *cmd)
{
	char	*name;
	char	*val;
	char	**ag;

	ag = cmd->ag;
	while (*ag)
	{
		name = ft_strndup(*ag, ft_strchri(*ag, '='));
		val = ft_strchr(*ag, '=') + 1;
		if (!env_get_ptr(*env, name))
			env_add(env, name, val, 0);
		else
			env_set_val(*env, name, val);
		free(name);
		ag++;
	}
}
