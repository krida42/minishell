/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:25:52 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/31 19:57:36 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	end_child(t_info *info)
{
	free_info(info);
	save_stdinout(2);
	close_std();
	return (g_err);
}

static int	child(t_cmd *cmd, t_info *info)
{
	char	**env_child;

	if (cmd->ag && cmd->fdin != -1 && cmd->fdout != -1
		&& dup_pipefds(cmd, info) != 1 && dup_filefds(cmd, info) != 1)
	{
		close_pipes_files(info->cmd);
		if (cmd->ag[0] && is_builtin(cmd) == 1)
			g_err = exec_builtin(cmd, info);
		else if (cmd->ag[0] && (cmd->ag[0] && cmd->ag[0][0]))
		{
			env_child = env_env_tostrs(info->env);
			cmd->cmd_path = command_path(cmd->ag, info->env);
			if (cmd->cmd_path != NULL)
			{
				execve(cmd->cmd_path, cmd->ag, env_child);
				perror("exec failed ");
			}
			free_strs(env_child);
		}
		exit(end_child(info));
	}
	close_pipes_files(info->cmd);
	exit (end_child(info));
}

static void	ft_waitpid(t_info *info)
{
	t_cmd	*tmp;

	tmp = info->cmd;
	while (tmp != NULL)
	{
		waitpid (tmp->pid, &tmp->status, 0);
		if (WIFEXITED(tmp->status))
			g_err = WEXITSTATUS(tmp->status);
		else if (WIFSIGNALED(tmp->status))
			g_err = 128 + WTERMSIG(tmp->status);
		if (WTERMSIG(tmp->status) == SIGSEGV)
			ft_puterr("Segmentation fault\n", NULL, NULL);
		tmp = tmp->next;
	}
	return ;
}

static void	pipex(t_cmd *cmd, t_info *info)
{
	while (cmd != NULL)
	{
		redefault_signals();
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			perror("fork failed ");
			close_pipes_files(info->cmd);
			return ;
		}
		else if (cmd->pid == 0)
			child(cmd, info);
		cmd = cmd->next;
	}
	close_pipes_files(info->cmd);
	ignore_signals();
	ft_waitpid(info);
	init_signals();
	save_stdinout(2);
	return ;
}

int	execute(t_info *info)
{
	if (save_stdinout(1) == 1)
		return (g_err);
	open_files(info->cmd, info);
	if (info->size == 1 && info->cmd->ag && is_builtin(info->cmd) == 1)
	{
		if (dup_filefds(info->cmd, info) == 0)
		{
			close_files(info->cmd);
			exec_builtin(info->cmd, info);
		}
		save_stdinout(2);
		return (g_err);
	}
	if (open_pipes(info->cmd, info) == 1)
		return (g_err);
	pipex(info->cmd, info);
	return (g_err);
}
