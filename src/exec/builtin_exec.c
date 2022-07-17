/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:31:02 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/17 17:35:11 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	exec_builtin(t_cmd *cmd, t_info *info) //20220717 ok
{
	(void)info;
	if (ft_strcmp(cmd->ag[0], "pwd") == 0)
		return(ft_builtin_pwd());
	// else if (ft_strcmp(cmd->ag[0], "cd") == 0)
	// 	return(ft_builtin_cd(cmd->ag[1]));
	else if (ft_strcmp(cmd->ag[0], "echo") == 0)
		return(ft_builtin_echo(cmd));
	// else if (ft_strcmp(cmd[0], "export") == 0)
	// 	ft_builtin_export();
	// else if (ft_strcmp(cmd[0], "unset") == 0)
	// 	ft_builtin_unset();
	// else if (ft_strcmp(cmd[0], "env") == 0)
	// 	ft_builtin_env();
	// else if (ft_strcmp(cmd[0], "exit") == 0)
	// 	ft_builtin_exit();
	return(1);
}

int	is_builtin(t_cmd *cmd) //20220717 ok
{
	if (ft_strcmp(cmd->ag[0], "pwd") == 0)
		return (1);
	// else if (ft_strcmp(cmd->ag[0], "cd") == 0)
	// 	return (1);
	else if (ft_strcmp(cmd->ag[0], "echo") == 0)
		return (1);
	// else if (ft_strcmp(cmd->ag[0], "export") == 0)
	// 	return (1);
	// else if (ft_strcmp(cmd->ag[0], "unset") == 0)
	// 	return (1);
	// else if (ft_strcmp(cmd->ag[0], "env") == 0)
	// 	return (1);
	// else if (ft_strcmp(cmd->ag[0], "exit") == 0)
	// 	return (1);
	return (0);
}