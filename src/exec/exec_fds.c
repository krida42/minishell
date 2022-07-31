/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:27:07 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/31 19:58:58 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_return_dup(char *str)
{
	perror(str);
	g_err = errno;
	return (1);
}

int	save_stdinout(int n)
{
	static int	tmpin;
	static int	tmpout;

	if (n == 1)
	{
		tmpin = dup(STDIN_FILENO);
		if (tmpin == -1)
			return (ft_return_dup("save_stdinout 1: in: dup: STDIN failed"));
		tmpout = dup(STDOUT_FILENO);
		if (tmpout == -1)
			return (ft_return_dup("save_stdinout 1: out: dup: STDOUT failed"));
	}
	if (n == 2)
	{
		if (dup2(tmpin, STDIN_FILENO) == -1)
			return (ft_return_dup("save_stdinout 2: in: dup2 failed"));
		if (close(tmpin) == -1)
			return (ft_return_dup("save_stdinout 2: in: close failed"));
		if (dup2(tmpout, STDOUT_FILENO) == -1)
			return (ft_return_dup("save_stdinout 2: out: dup2 failed"));
		if (close(tmpout))
			return (ft_return_dup("save_stdinout 2: out: close failed"));
	}
	return (0);
}

int	dup_filefds(t_cmd *cmd, t_info *info)
{
	(void)info;
	if (cmd->fdin >= 0 && (cmd->in != NULL || cmd->heredoc != NULL))
	{
		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
			return (ft_return_dup("dup_filefds: fdin: dup2 failed"));
	}
	if (cmd->fdout >= 0 && (cmd->out != NULL || cmd->append != NULL))
	{
		if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
			return (ft_return_dup("dup_filefds: fdout: dup2 failed"));
	}
	return (0);
}

int	dup_pipefds(t_cmd *cmd, t_info *info)
{
	(void)info;
	if (cmd->prev != NULL && cmd->in == NULL && cmd->heredoc == NULL)
	{
		if (dup2(cmd->prev->pipefd[0], STDIN_FILENO) == -1)
			return (ft_return_dup("dup_pipefds: fdin: dup2 failed"));
	}
	if (cmd->next != NULL && cmd->out == NULL && cmd->append == NULL)
	{
		if (dup2(cmd->pipefd[1], STDOUT_FILENO) == -1)
			return (ft_return_dup("dup_pipefds: fdout: dup2 failed"));
	}
	return (0);
}
