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

static int	eve_exec(t_env *env, char **args, int is_exec)
{
	char	*path;
	char	**envp;
	char	*cmd_path;

	if (!is_exec)
		eve_display(env);
	else
	{
		path = env_get_val(env, "PATH");
		cmd_path = command_path(args, env);
		envp = env_env_tostrs(env);
		if (fork() == 0)
			execve(cmd_path, args, envp);
		free(path);
		free_strs(envp);
	}
	return (0);
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
	eve_exec(new_env, args, is_exec);
	free_allenv(new_env);
	return (0);
}
