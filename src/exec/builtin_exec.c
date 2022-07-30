/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:31:02 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/30 17:41:02 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *cmd, t_info *info) //20220717 ok
{
	// (void)info;
	if (ft_strcmp(cmd->ag[0], "pwd") == 0)
		return(ft_builtin_pwd());
	else if (ft_strcmp(cmd->ag[0], "cd") == 0)
		return(ft_builtin_cd(cmd->ag, info->env));
	else if (ft_strcmp(cmd->ag[0], "echo") == 0)
		return(ft_builtin_echo(cmd));
	else if (ft_strcmp(cmd->ag[0], "export") == 0)
		return (b_export(info, cmd->ag + 1));
	else if (ft_strcmp(cmd->ag[0], "unset") == 0)
		return (b_unset(info, cmd->ag + 1));
	else if (ft_strcmp(cmd->ag[0], "env") == 0)
		return (b_env(info, cmd->ag + 1));
	else if (ft_strcmp(cmd->ag[0], "exit") == 0)
		return (ft_builtin_exit(cmd->ag));
	return(1);
}

int	is_builtin(t_cmd *cmd) //20220717 ok
{
	if (ft_strcmp(cmd->ag[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->ag[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->ag[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->ag[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->ag[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->ag[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->ag[0], "exit") == 0)
		return (1);
	return (0);
}
