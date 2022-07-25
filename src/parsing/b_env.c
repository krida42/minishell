#include "minishell.h"
#include <stdio.h>


static void	eve_display(t_env *env)
{
	while (env)
	{
		if (env->val)
			printf("%s=%s\n", env->name, env->val);
		env = env->next;
	}
}

static void	eve_addvarinit(t_env **env, char *s)
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

int	b_env(t_info *info, char **args)
{
	t_env	*new_env;
	int		is_exec;

	if (!args)
		exit(printf(RED"DANGER - b_env() - args is NULL"WHITE));
	new_env = env_dup(info->env);
	is_exec = 0;
	while (*args)
	{
		if (!is_varinit(*args))
		{
			is_exec = 1;
			break;
		}
		eve_addvarinit(&new_env, *args);
		args++;
	}
	if (!is_exec)
		eve_display(new_env);
	free_allenv(new_env);
	return (0);
}
