/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:25:52 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/28 09:10:35 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_cmd_files(t_cmd *cmd, t_info *info) //20220717 ok
{
	if (cmd->in != NULL)
		cmd->fdin = open(cmd->in, O_RDONLY);
	else if (cmd->heredoc != NULL)
		cmd->fdin = open(cmd->heredoc, O_RDONLY);
	if (cmd->fdin == -1)
	{
		perror(cmd->in);
		info->error_n = errno;
		return (1);
	}
	if (cmd->out != NULL)
		cmd->fdout = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->append != NULL)
		cmd->fdout = open(cmd->append, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fdout == -1)
	{
		perror(cmd->out);
		info->error_n = errno;
		return (1);
	}
	return (0);
}

// void	open_files(t_cmd *cmd) //20220717 ok
// {
// 	while(cmd)
// 	{
// 		if (cmd->in != NULL)
// 		{
// 			cmd->fdin = open(cmd->in, O_RDONLY);
// 			if (cmd->fdin == -1)
// 				perror(cmd->in);
// 			// fprintf(stderr,"in fdin %d\n", cmd->fdin);
// 		}
// 		else if (cmd->heredoc != NULL)
// 		{
// 			cmd->fdin = open(cmd->heredoc, O_RDONLY);
// 		}
// 		if (cmd->out != NULL)
// 		{
// 			cmd->fdout = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (cmd->fdout == -1)
// 				perror(cmd->out);
// 			// fprintf(stderr,"out fdout %d\n", cmd->fdout);
// 		}
// 		else if (cmd->append != NULL)
// 		{
// 			cmd->fdout = open(cmd->append, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (cmd->fdout == -1)
// 				perror(cmd->out);
// 			// fprintf(stderr,"append fdout %d\n", cmd->fdout);
// 		}
// 		cmd = cmd->next;
// 	}
// }

int	open_pipes(t_cmd *cmd, t_info *info) //20220717 ok // voir pour free info
{
	while (cmd->next != NULL)
	{
		if (pipe(cmd->pipefd) == -1)
		{
			perror("pipe failed");
			info->error_n = errno;
			// close_files(info->cmd);
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
