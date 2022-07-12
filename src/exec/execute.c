/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:25:52 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/11 18:13:59 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_fd(int fd, int stdstream_no, t_info *info)
{
	if (fd == -1)
	{
		close_pipes(info->cmd);
		close_files(info->cmd);
		ft_free(info);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, stdstream_no) == -1)
		msg_close_free_exit("dup2 failed ", info);
}

static void	dupfds(t_cmd *cmd, t_info *info)
{
	if (cmd->prev)
	{
		if (dup2(cmd->prev->pipefd[0], STDIN_FILENO) < 0)
			msg_close_free_exit("dup2 failed", info);
	}
	if (cmd->next)
	{
		if (dup2(cmd->pipefd[1], STDOUT_FILENO) < 0)
			msg_close_free_exit("dup2 failed", info);
	}
}

void	one_cmd(t_cmd *cmd, t_info *info)
{
	if (exec_builtin(cmd, info) == 0)
	{
		close_std();
		ft_free(info);
		exit(EXIT_SUCCESS); // voir status de retour 0 si exec ok 1 si pas de buitlin autre chiffre si erreur?
	}
	else
	{
		cmd->cmd_path = command_path(cmd->ag, info);
		if (execve(cmd->cmd_path, cmd->ag, info->env) == -1)
			msg_close_free_exit("execve failed", info);
	}
}

static void	child(t_cmd *cmd, t_info *info)
{
	if (info->size == 1)
		one_cmd(cmd, info);
	dupfds(cmd, info);
	close_pipes(info->cmd);
	if (cmd->in != NULL || cmd->out != NULL || cmd->append != NULL
		|| cmd->heredoc)
	{
		redirect_fd(cmd->fdin, STDIN_FILENO, info);
		redirect_fd(cmd->fdout, STDOUT_FILENO, info);
	}
	one_cmd(cmd, info);
}

static void	pipex(t_cmd *cmd, t_info *info)
{
	int	status;
	
	cmd->pid = fork();
	if (cmd->pid == -1)
		msg_close_free_exit("fork failed", info);
	else if (cmd->pid == 0)
	{
		//signal(SIGQUIT, ft_handler_exec);
		//signal(SIGQUIT, ft_shandler); //Interruption forte (ctrl-\)//Terminaison + core dump
		child(cmd, info);
	}
	if (cmd->next)
		pipex(cmd->next, info);
	close_pipes(info->cmd);
	while (cmd)
	{
		waitpid (cmd->pid, &status, 0); // revoir NULL sur status WEXITSTATUS, WIFSIGNALED
		//if (WIFEXITED(status))
		//	//x = WEXITSTATUS(status) // returns the exit status of the child. exit etc
		//else if (WIFSIGNALED(status))
		//	//x = WTERMSIG(status); //returns the number of the signal that caused the child process to terminate. This macro should only be employed if WIFSIGNALED returned true
		cmd = cmd->next;
	}
}

void	execute(t_info *info)
{
	if (info->cmd->next == NULL && is_builtin(info->cmd) == 1) // juste pour les builtin, cd... voir pour else in one_cmd
		one_cmd(info->cmd, info);
	else
	{
		open_pipes(info->cmd, info);
		open_files(info->cmd);
		pipex(info->cmd, info);
	}
	ft_free(info); // voir avec Kévin pour n'est pas faire 2x
	close_std();
}

// static void	pipex(t_cmd *cmd, t_info *info)
// {
// 	t_cmd	*tmp;
	
// 	while (cmd)
// 	{
// 		cmd->pid = fork();
// 		// open_files(info->cmd);
// 		if (cmd->pid == -1)
// 			msg_close_free_exit("fork failed", info);
// 		else if (cmd->pid == 0)
// 		{
// 			//singal//
// 			child(cmd, info);
// 		}
// 		cmd = cmd->next;
// 	}
// 	close_pipes(info->cmd);
// 	tmp = info->cmd;
// 	while (tmp)
// 	{
// 		waitpid (tmp->pid, NULL, 0); // revoir NULL sur status
// 		tmp = tmp->next;
// 	}
// }

// static void	dup_fd(int fd, int stdstream_no, t_cmd *cmd, t_info *info)
// {
// 	if (cmd)
// 	{
// 		if (dup2(fd, stdstream_no) == -1)
// 			msg_close_free_exit("dup2 failed", info);
// 	}
// }
//dans le child
	// if (cmd->prev)
	// 	dup_fd(cmd->prev->pipefd[0], STDIN_FILENO, cmd->prev, info);
	// // if (cmd->next)
	// 	dup_fd(cmd->pipefd[1], STDOUT_FILENO, cmd->next, info);