/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:24:28 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 19:24:29 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_env_tostrs(t_env *env)
{
	char	**strs;
	char	*name_j;
	char	*str_new;

	strs = NULL;
	while (env)
	{
		if (env->is_export && env->val)
		{
			name_j = ft_strjoin(env->name, "=");
			str_new = ft_strjoin(name_j, env->val);
			strs_insert(&strs, str_new);
			free(name_j);
			free(str_new);
		}
		env = env->next;
	}
	return (strs);
}

t_env	*env_strs_toenv(char **strs_envp)
{
	t_env	*env;
	char	*name;
	char	*val;

	env = NULL;
	while (*strs_envp)
	{
		name = ft_strndup(*strs_envp, ft_strchri(*strs_envp, '='));
		val = ft_strchr(*strs_envp, '=') + 1;
		env_add(&env, name, val, 1);
		free(name);
		strs_envp++;
	}
	return (env);
}

t_env	*env_dup(t_env *env)
{
	t_env	*dup;

	dup = NULL;
	while (env)
	{
		env_add(&dup, env->name, env->val, env->is_export);
		env = env->next;
	}
	return (dup);
}
