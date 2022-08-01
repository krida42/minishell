/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:11:41 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 20:11:41 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_rm(t_env **env, char *name)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			if (!cur->prev)
				*env = cur->next;
			else
				(cur->prev)->next = cur->next;
			if (cur->next)
				(cur->next)->prev = cur->prev;
			free_env(cur);
			return ;
		}
		cur = cur->next;
	}
	exit(printf(RED"DANGER - : Trying to remove a variable that doesnt "
			"exist !\n"WHITE));
}

void	env_set_val(t_env *env, char *name, char *val)
{
	env = env_get_ptr(env, name);
	if (!env)
		exit(printf(RED"DANGER - - env_set_val : Trying to edit a variable "
				"that doesnt exist\n"WHITE));
	free(env->val);
	env->val = ft_strdup(val);
}

void	env_set_export(t_env *env, char *name, int is_export)
{
	env = env_get_ptr(env, name);
	if (!env)
		exit(printf(RED"DANGER - - env_set_export : setting is_export for "
				"var that doesnt exist\n"WHITE));
	env->is_export = is_export;
}

t_env	*env_get_ptr(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*env_get_val(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (ft_strdup(env->val));
		env = env->next;
	}
	return (NULL);
}
