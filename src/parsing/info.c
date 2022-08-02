/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:01:41 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/02 02:05:46 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*t_info	*init_info(t_cmd *cmd, char **envp)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->cmd = cmd;
	info->env = env_strs_toenv(envp);
	info->size = cmd_size(cmd);
	return (info);
}*/

t_info	*init_info(char **envp)
{
	t_info	*info;
	char	*shlvl;

	info = malloc(sizeof(t_info));
	info->env = env_strs_toenv(envp);
	info->cmd = NULL;
	info->size = cmd_size(info->cmd);
	info->error_n = 0;
	shlvl = ft_itoa(ft_atoi(env_get_ptr(info->env, "SHLVL")->val) + 1);
	env_set_val(info->env, "SHLVL", shlvl);
	free(shlvl);
	return (info);
}

void	set_cmd(t_info *info, t_cmd *cmd)
{
	info->cmd = cmd;
	info->size = cmd_size(cmd);
}

void	reset_info(t_info *info)
{
	free_allcmd(info->cmd);
	set_cmd(info, NULL);
}

void	free_info(t_info *info)
{
	free_allcmd(info->cmd);
	free_allenv(info->env);
	free(info);
}
