/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:00:07 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 20:00:08 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void	export_varinit(t_env **env, char *s)
{
	char	*name;
	char	*val;

	name = ft_strndup(s, ft_strchri(s, '='));
	val = ft_strchr(s, '=') + 1;
	if (env_get_ptr(*env, name))
	{
		env_set_val(*env, name, val);
		env_set_export(*env, name, 1);
	}
	else
		env_add(env, name, val, 1);
	free(name);
}

static void	export_identifier(t_env **env, char *name)
{
	if (env_get_ptr(*env, name))
		env_set_export(*env, name, 1);
	else
		env_add(env, name, NULL, 1);
}

static void	export_display(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->name);
		if (env->val)
			printf("=\"%s\"", env->val);
		printf("\n");
		env = env->next;
	}
}

int	b_export(t_info *info, char **args)
{
	if (!args)
		exit(printf(RED"DANGER - b_export() - args is NULL"WHITE));
	if (!*args)
		return (export_display(info->env), 0);
	while (*args)
	{
		if (is_varinit(*args))
			export_varinit(&info->env, *args);
		else if (is_validid(*args))
			export_identifier(&info->env, *args);
		else
			ft_puterr(RED"minishell: export: `", *args, "': not a valid "
				"identifier\n"WHITE);
		args++;
	}
	return (0);
}
