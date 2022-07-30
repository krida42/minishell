/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:25:52 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/30 18:32:49 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	msg_open(char *str)
{
	perror(str);
	g_err = 1;
}

void	open_files(t_cmd *cmd, t_info *info) //20220717 ok
{
	(void)info;
	while(cmd)
	{
		if (cmd->in != NULL)
			cmd->fdin = open(cmd->in, O_RDONLY);
		else if (cmd->heredoc != NULL)
			cmd->fdin = open(cmd->heredoc, O_RDONLY);
		if (cmd->fdin == -1)
			msg_open(cmd->in);
		else if (cmd->heredoc != NULL)
		{
			if (unlink(cmd->heredoc) == -1)
				msg_open(cmd->heredoc);
		}
		// {
		// 	perror(cmd->in);
		// 	g_err = errno;
		// }
		if (cmd->out != NULL)
			cmd->fdout = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cmd->append != NULL)
			cmd->fdout = open(cmd->append, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->fdout == -1)
			msg_open(cmd->out);
		// {
		// 	perror(cmd->out);
		// 	g_err = errno;
		// }
		cmd = cmd->next;
	}
}

int	open_pipes(t_cmd *cmd, t_info *info) //20220717 ok // voir pour free info
{
	(void)info;
	while (cmd->next != NULL)
	{
		if (pipe(cmd->pipefd) == -1)
		{
			perror("pipe failed");
			g_err = 1;
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
