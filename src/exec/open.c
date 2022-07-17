/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:25:52 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/17 17:34:33 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_files(t_cmd *cmd) //20220717 ok
{
	if (cmd->in != NULL)
	{
		cmd->fdin = open(cmd->in, O_RDONLY);
		if (cmd->fdin == -1)
			perror(cmd->in);
		fprintf(stderr,"in fdin %d\n", cmd->fdin);
	}
	if (cmd->out != NULL)
	{
		cmd->fdout = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fdout == -1)
			perror(cmd->out);
		fprintf(stderr,"out fdout %d\n", cmd->fdout);
	}
	else if (cmd->append != NULL)
	{
		cmd->fdout = open(cmd->append, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->fdout == -1)
			perror(cmd->out);
		fprintf(stderr,"append fdout %d\n", cmd->fdout);
	}
}

void	open_pipes(t_cmd *cmd, t_info *info) //20220717 ok // voir pour free info
{
	while (cmd->next != NULL)
	{
		if (pipe(cmd->pipefd) == -1)
			msg_close_free_exit("pipe failed", info);
		cmd = cmd->next;
	}
}
