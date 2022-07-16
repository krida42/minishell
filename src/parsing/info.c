#include "minishell.h"

t_info	*init_info(t_cmd *cmd, char **envp)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->cmd = cmd;
	info->env = env_strs_toenv(envp);
	info->path = env_get_ptr(info->env, "PATH")->val;
	info->size = cmd_size(cmd);
	return (info);
}

void	free_info(t_info *info)
{
	free_allcmd(info->cmd);
	free_allenv(info->env);
	free(info);
}
