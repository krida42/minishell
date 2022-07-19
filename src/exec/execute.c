/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:25:52 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/19 22:36:37 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	save_stdinout(int n) //20220717 ok
{
	static int	tmpin;
	static int	tmpout;

	if (n == 1)
	{
		tmpin = dup(STDIN_FILENO);
		tmpout = dup(STDOUT_FILENO);
	}
	if (n == 2)
	{
		if (dup2(tmpin, STDIN_FILENO) == -1)
		{
			perror("dup2 failed save_stdinout 2 temp in");
			return (1);
		}
		close(tmpin);
		if (dup2(tmpout, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed save_stdinout  2 temp in");
			return (1);
		}
		close(tmpout);
	}
	return (0);
}

static int	dup_filefds(t_cmd *cmd, t_info *info) //20220717 ok
{
	if (cmd->in != NULL || cmd->heredoc != NULL)
	{
		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
		{
			perror("dup2 failed dup_filefds in ");
			close_files(info->cmd);
			exit (1);
		}
	}
	if (cmd->out != NULL || cmd->append != NULL)
	{
		if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed dup_filefds out ");
			close_files(info->cmd);
			exit (1);
		}
	}
	return (0);
}

static int	dup_pipefds(t_cmd *cmd, t_info *info)
{
	if (cmd->prev != NULL && cmd->in == NULL && cmd->heredoc == NULL) // && cmd->prev->out == NULL && cmd->prev->append == NULL
	{
		if (dup2(cmd->prev->pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 failed dup_pipefds in ");
			close_pipes(info->cmd);
			exit (1);
		}
	}
	if (cmd->next != NULL && cmd->out == NULL && cmd->append == NULL) //&& cmd->next->in == NULL && cmd->next->heredoc == NULL
	{
		if (dup2(cmd->pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed dup_pipefds in ");
			close_pipes(info->cmd);
			exit (1);
		}
	}
	return (0);
}

static void	child(t_cmd *cmd, t_info *info)
{
	char	**env_child;

	env_child = env_env_tostrs(info->env);
	dup_pipefds(cmd, info);
	close_pipes(info->cmd);
	dup_filefds(cmd, info);
	close_files(info->cmd);
	if (is_builtin(cmd) == 1)
	{
		if (exec_builtin(cmd, info) == 1)
			exit (1);
	}
	else
	{
		cmd->cmd_path = command_path(cmd->ag, info);
		// if (execve(cmd->cmd_path, cmd->ag, info->env) == -1)
		if (execve(cmd->cmd_path, cmd->ag, env_child) == -1)
		perror("exec failed ");
		exit (1);
	}
	exit (0) ;
}

static void	pipex(t_cmd *cmd, t_info *info) //20220717 ok
{
	// int		status;
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
		{
			perror("fork failed ");
			close_pipes(info->cmd);
			close_files(info->cmd);
			return ;
		}
		else if (tmp->pid == 0)
		{
			{
				//signal(SIGQUIT, ft_shandler); //Interruption forte (ctrl-\)//Terminaison + core dump
				child(tmp, info);
			}
		}
		tmp = tmp->next;
	}
	// fprintf(stderr,"pipex after while\n");
	close_pipes(info->cmd);
	close_files(info->cmd);
	tmp = info->cmd;
	while (tmp != NULL)
	{
		// fprintf(stderr,"waitpid start tmp->ag[0] is %s\n", tmp->ag[0]);
		waitpid (tmp->pid, NULL, 0); // revoir NULL sur status WEXITSTATUS, WIFSIGNALED
		// waitpid (tmp->pid, &status, 0); // revoir NULL sur status WEXITSTATUS, WIFSIGNALED
		//if (WIFEXITED(status))
		//	//x = WEXITSTATUS(status) // returns the exit status of the child. exit etc
		//else if (WIFSIGNALED(status))
		//	//x = WTERMSIG(status); //returns the number of the signal that caused the child process to terminate. This macro should only be employed if WIFSIGNALED returned true
		// fprintf(stderr,"waitpid done tmp->ag[0] is %s\n", tmp->ag[0]);
		tmp = tmp->next;
	}
	// fprintf(stderr,"after waitpid\n");
	save_stdinout(2);
	return ;
}

void	execute(t_info *info) //20220717 ok
{
	save_stdinout(1);
	open_files(info->cmd);
	if (info->size == 1 && is_builtin(info->cmd) == 1)
	{
		if (exec_builtin(info->cmd, info) == 1)
		{
			close_files(info->cmd);
			return ;
		}
		if (dup_filefds(info->cmd, info) == 1)
		{
			close_files(info->cmd);
			return (perror("dup_filesfd failed "));
		}
		save_stdinout(2);
	}
	else
	{
		open_pipes(info->cmd, info);
		pipex(info->cmd, info);
	}
	// fprintf(stderr,"execute pipex done\n");
	// save_stdinout(2);
	return ;
}

/* rien ne va pas... 20220717*/
// // static void	dupfds(t_cmd *cmd, t_info *info)
// // {
// // 	fprintf(stderr,"dupfds start\n");
// // 	if (cmd->prev)
// // 	{
// // 		if (dup2(cmd->prev->pipefd[0], STDIN_FILENO) < 0)
// // 			msg_close_free_exit("dup2 failed", info);
// // 	}
// // 	if (cmd->next)
// // 	{
// // 		if (dup2(cmd->pipefd[1], STDOUT_FILENO) < 0)
// // 			msg_close_free_exit("dup2 failed", info);
// // 	}
// // }

// // static int	dupfds_file(t_cmd *cmd)
// // {
// // 	fprintf(stderr,"dupfds files start\n");
// // 	if (cmd->fdin == -1 ||cmd->fdout == -1)
// // 	{
// // 		close_pipes(cmd);
// // 		close_files(cmd);
// // 		exit (1);// a voir pour l'erreur
// // 	}
// // 	if (cmd->in != NULL || cmd->heredoc != NULL)
// // 	{
// // 		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
// // 		{
// // 			close_pipes(cmd);
// // 			close_files(cmd);
// // 			exit (1);// a voir pour l'erreur
// // 		}
// // 	}
// // 	if (cmd->out != NULL || cmd->append != NULL)
// // 	{
// // 		if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
// // 		{
// // 			close_pipes(cmd);
// // 			close_files(cmd);
// // 			exit (1);// a voir pour l'erreur
// // 		}
// // 	}
// // 	return (0);
// // }

// static int	dupfd_in(t_cmd *cmd)
// {
// 	if (cmd->prev) // && cmd->prev->out == NULL && cmd->prev->append == NULL
// 	{
// 		if (dup2(cmd->prev->pipefd[0], STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 failed dupfds in pipefd[0] ");
// 			return (1);
// 		}
// 	}
// 	if (cmd->fdin == -1)
// 	{

// 		return (1); ;// a voir pour l'erreur
// 	}
// 	if (cmd->in != NULL || cmd->heredoc != NULL)
// 	{
// 		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 failed dupfds fdin ");
// 			exit (1);
// 		}
// 	}
// 	return (0);
// }

// static int	dupfd_out(t_cmd *cmd)
// {
// 	if (cmd->next) // && cmd->next->in == NULL && cmd->next->heredoc == NULL
// 	{
// 		if (dup2(cmd->pipefd[1], STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 failed dupfds in pipefd[1] ");
// 			return (1);
// 		}
// 	}
// 	if (cmd->fdout == -1)
// 	{
// 		close_pipes(cmd);
// 		close_files(cmd);
// 		exit (1) ;// a voir pour l'erreur
// 	}
// 	if (cmd->out != NULL || cmd->append != NULL)
// 	{
// 		if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 failed dupfds fdout ");
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// static void	child(t_cmd *cmd, t_info *info)
// {
// 	fprintf(stderr,"cmd %s\n",cmd->ag[0]);
// 	if (dupfd_in(cmd) == 1 || dupfd_out(cmd) == 1)
// 	{
// 		close_pipes(cmd);
// 		close_files(cmd);
// 		exit (1);
// 	}
// 	// dupfds(cmd, info);
// 	// close_pipes(info->cmd);
// 	// dupfds_file(cmd);
// 	// close_files(info->cmd);
// 	if (is_builtin(cmd) == 1)
// 	{
// 		if (exec_builtin(cmd, info) == 1)
// 		{
// 			perror("exec_built in failed ") ;
// 			exit (1);
// 		}
// 		exit (0);
// 	}
// 	else
// 	{
// 		cmd->cmd_path = command_path(cmd->ag, info);
// 		if (execve(cmd->cmd_path, cmd->ag, info->env) == -1)
// 			msg_close_return("execve failed", info);
// 	}
// }

// // static void	pipex(t_cmd *cmd, t_info *info)
// // {
// // 	t_cmd	*tmp;
	
// // 	fprintf(stderr,"pipex start\n");
// // 	while (cmd)
// // 	{
// // 		cmd->pid = fork();
// // 		// open_files(info->cmd);
// // 		if (cmd->pid == -1)
// // 			msg_close_free_exit("fork failed", info);
// // 		else if (cmd->pid == 0)
// // 		{
// // 			//singal//
// // 			child(cmd, info);
// // 		}
// // 		cmd = cmd->next;
// // 	}
// // 	close_pipes(info->cmd);
// // 	tmp = info->cmd;
// // 	while (tmp)
// // 	{
// // 		waitpid (tmp->pid, NULL, 0); // revoir NULL sur status
// // 		tmp = tmp->next;
// // 	}
// // }

// /* NOTE
//  a clarifier redirection fds car pas claire du tout le pricipe
//  en plus fermeture des fds pipes et files aussi a un impact
 
//   retracer ce que se passe avec dup2 car vraiment bizzarre 
//   En plus gestion d erreur n'est pas clarifié*/
  
// static void	pipex(t_cmd *cmd, t_info *info)
// {
// 	int	status;
		
// 	cmd->pid = fork();
// 	if (cmd->pid == -1)
// 		msg_close_return("fork failed", info);
// 	else if (cmd->pid == 0)
// 	{
// 		//signal(SIGQUIT, ft_handler_exec);
// 		//signal(SIGQUIT, ft_shandler); //Interruption forte (ctrl-\)//Terminaison + core dump
// 		child(cmd, info);
// 	}
// 	if (cmd->next != NULL)
// 		pipex(cmd->next, info);
// 	// close_pipes(info->cmd);
// 	// close_files(info->cmd);
// 	while (cmd != NULL)
// 	{
// 		waitpid (cmd->pid, &status, 0); // revoir NULL sur status WEXITSTATUS, WIFSIGNALED
// 		//if (WIFEXITED(status))
// 		//	//x = WEXITSTATUS(status) // returns the exit status of the child. exit etc
// 		//else if (WIFSIGNALED(status))
// 		//	//x = WTERMSIG(status); //returns the number of the signal that caused the child process to terminate. This macro should only be employed if WIFSIGNALED returned true
// 		cmd = cmd->next;
// 	}
// 	return ;
// }

// static int	save_stdinout(int n)
// {
// 	static int	tmpin;
// 	static int	tmpout;

// 	if (n == 1)
// 	{
// 		tmpin = dup(STDIN_FILENO);
// 		tmpout = dup(STDOUT_FILENO);
// 	}
// 	if (n == 2)
// 	{
// 		if (dup2(tmpin, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 failes save_stdinout ");
// 			return (1);
// 		}
// 		if (dup2(tmpout, STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 failes save_stdinout ");
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// void	execute(t_info *info)
// {
// 	open_files(info->cmd);
// 	save_stdinout(1);
// 	if (info->cmd->next == NULL && is_builtin(info->cmd) == 1) // juste pour les builtin, cd... voir pour else in one_cmd
// 	{
// 		if (dupfd_in(info->cmd) == 1 || dupfd_out(info->cmd) == 1)
// 		{
// 			close_files(info->cmd);
// 			return ;
// 		}
// 		if (exec_builtin(info->cmd, info) == 1)
// 		{
// 			close_files(info->cmd);
// 			save_stdinout(2);
// 		}
// 	}
// 	else
// 	{
// 		open_pipes(info->cmd, info);
// 		pipex(info->cmd, info);
// 	}
// }
