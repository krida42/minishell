#include "minishell.h"

int	b_unset(t_info *info, char **args)
{
	while (*args)
	{
		if (env_get_ptr(info->env, *args))
			env_rm(&info->env, *args);
		args++;
	}
	return (0);
}
