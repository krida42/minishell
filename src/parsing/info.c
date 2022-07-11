#include "minishell.h"

t_info	*init_info(t_cmd *cmd, t_env *env)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->cmd = cmd;
	info->env = env_env_tostrs(env);
	info->path = env_get_val(env, "PATH");
	info->size = cmd_size(cmd);
	return (info);
}

void	free_info(t_info *info)
{
	free_allcmd(info->cmd);
	free_strs(info->env);
	free(info->path);
	free(info);
}
