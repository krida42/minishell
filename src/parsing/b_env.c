#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static void	eve_display(t_env *env)
{
	while (env)
	{
		if (env->val)
			printf("%s=%s\n", env->name, env->val);
		env = env->next;
	}
}

int	b_env(t_info *info, char **args)
{
	if (!args)
		exit(printf(RED"DANGER - b_env() - args is NULL"WHITE));
	if (*args)
	{
		ft_puterr(RED"env: ", *args , ": arguments not allowed\n"WHITE);
		return (1);
	}
	eve_display(info->env);
	return (0);
}
