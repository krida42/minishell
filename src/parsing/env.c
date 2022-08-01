/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:10:08 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 20:13:00 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static t_env	*new_env(char *name, char *val, int is_export)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->name = ft_strdup(name);
	env->val = NULL;
	if (val)
		env->val = ft_strdup(val);
	env->is_export = is_export;
	env->prev = NULL;
	env->next = NULL;
	return (env);
}

static void	env_add_lexico(t_env **env, t_env *new)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->name, new->name) > 0)
		{
			new->prev = cur->prev;
			new->next = cur;
			if (!cur->prev)
				*env = new;
			else
				(cur->prev)->next = new;
			cur->prev = new;
			return ;
		}
		else if (!cur->next)
		{
			new->prev = cur;
			cur->next = new;
			return ;
		}
		cur = cur->next;
	}
}

void	env_add(t_env **env, char *name, char *val, int is_export)
{
	t_env	*new;

	new = new_env(name, val, is_export);
	if (!*env)
	{
		*env = new;
		return ;
	}
	env_add_lexico(env, new);
}

void	free_env(t_env *env)
{
	free(env->name);
	free(env->val);
	free(env);
}

void	free_allenv(t_env *env)
{
	if (!env)
		return ;
	while (env->next)
	{
		env = env->next;
		free_env(env->prev);
	}
	free_env(env);
}
