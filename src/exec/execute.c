/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:25:52 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/29 21:31:55 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	freeinfo_exit(int exit_n, t_info *info)
// {
// 	free_info(info);
// 	exit (exit_n);
// }

// static int	child(t_cmd *cmd, t_info *info)
// {
// 	char	**env_child;

// 	if (cmd->fdin == -1 || cmd->fdout == -1) // appel syst errno sera defini auto
// 	{
// 		close_pipes_files(info->cmd);
// 		freeinfo_exit(errno, info);
// 	}
// 	if (dup_pipefds(cmd, info) == 1 || dup_filefds(cmd, info) == 1) // appel syst errno sera defini auto
// 	{
// 		close_pipes_files(info->cmd);
// 		freeinfo_exit(errno, info);
// 	}
// 	close_pipes_files(info->cmd);
// 	if (is_builtin(cmd) == 1)
// 	{
// 		if (exec_builtin(cmd, info) == 1)
// 		{
// 			close_pipes_files(info->cmd);
// 			freeinfo_exit(EXIT_FAILURE, info);
// 		}
// 	}
// 	else if (cmd->ag[0] != NULL && (cmd->ag[0] && cmd->ag[0][0]))
// 	{
// 		env_child = env_env_tostrs(info->env);
// 		cmd->cmd_path = command_path(cmd->ag, info->env);
// 		if (cmd->cmd_path != NULL)
// 		{
// 			execve(cmd->cmd_path, cmd->ag, env_child); 
// 				perror("exec failed ");
// 		}
// 		free_strs(env_child);
// 		freeinfo_exit(errno, info);
// 	}
// 	return(freeinfo_exit(EXIT_SUCCESS, info));
// }

static int	child(t_cmd *cmd, t_info *info)
{
	char	**env_child;

	if (cmd->fdin != -1 && cmd->fdout != -1 && dup_pipefds(cmd, info) != 1
		&& dup_filefds(cmd, info) != 1)
	{
		close_pipes_files(info->cmd);
		if (is_builtin(cmd) == 1)
			info->error_n = exec_builtin(cmd, info);
		else if (cmd->ag[0] != NULL && (cmd->ag[0] && cmd->ag[0][0]))
		{
			env_child = env_env_tostrs(info->env);
			cmd->cmd_path = command_path(cmd->ag, info->env); // option d'optimisation
			if (cmd->cmd_path != NULL)
			{
				execve(cmd->cmd_path, cmd->ag, env_child); 
					perror("exec failed ");
			}
			// info->error_n = errno;
			free_strs(env_child);
		}
	}
	close_pipes_files(info->cmd);
	free_info(info);
	save_stdinout(2);
	close_std();
	exit (errno);
}

static void	ft_waitpid(t_info *info)
{
	t_cmd	*tmp;
	
	tmp = info->cmd;
	while (tmp != NULL)
	{
		// waitpid (tmp->pid, NULL, 0); // revoir NULL sur status WEXITSTATUS, WIFSIGNALED
		waitpid (tmp->pid, &tmp->status, 0); // revoir NULL sur status WEXITSTATUS, WIFSIGNALED
		if (WIFEXITED(tmp->status))
			info->error_n = WEXITSTATUS(tmp->status); // returns the exit status of the child. exit etc
		else if (WIFSIGNALED(tmp->status))
			info->error_n = WTERMSIG(tmp->status); //returns the number of the signal that caused the child process to terminate. This macro should only be employed if WIFSIGNALED returned true
		tmp = tmp->next;
	}
	return ;
}

static int	pipex(t_cmd *cmd, t_info *info) //20220717 ok
{
	while (cmd != NULL)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			perror("fork failed ");
			close_pipes(info->cmd);
			return (errno);
		}
		else if (cmd->pid == 0)
		{
			save_stdinout(2);
			child(cmd, info);
		}
		cmd = cmd->next;
	}
	close_pipes_files(info->cmd);
	init_signals();
	ft_waitpid(info);
	save_stdinout(2); // doit être ici car il n'y a qu'1 return à la fin dans l'execute
	return (info->error_n);
}

int	execute(t_info *info) //20220717 ok
{
	if (save_stdinout(1) == 1)
		return (errno);
	open_files(info->cmd, info);
	if (info->size == 1 && is_builtin(info->cmd) == 1)
	{
		if (info->error_n == 1 || dup_filefds(info->cmd, info) == 1)
		{
			save_stdinout(2);
			return (errno);
		}
		close_files(info->cmd);
		if (exec_builtin(info->cmd, info) == 1)
		{
			save_stdinout(2);
			return (1);
		}
		save_stdinout(2);
		return (0);
	}
	if (open_pipes(info->cmd, info) == 1)
		return (errno);
	return(pipex(info->cmd, info));
}

/*child 2 reserve 20220728*/
// static int	child(t_cmd *cmd, t_info *info)
// {
// 	char	**env_child;

// 	if (cmd->fdin == -1 || cmd->fdout == -1) // appel syst errno sera defini auto
// 	{
// 		close_files(info->cmd);
// 		close_pipes(info->cmd);
// 		free_info(info);
// 		save_stdinout(2);
// 		close_std();
// 		exit (errno);
// 	}
// 	else if (dup_pipefds(cmd, info) == 1 || dup_filefds(cmd, info) == 1) // appel syst errno sera defini auto
// 	{
// 		close_files(info->cmd);
// 		close_pipes(info->cmd);
// 		free_info(info);
// 		save_stdinout(2);
// 		close_std();
// 		exit (errno);
// 	}
// 	close_pipes(info->cmd);
// 	close_files(info->cmd);
// 	if (is_builtin(cmd) == 1)
// 	{
// 		if (exec_builtin(cmd, info) == 1)
// 		{
// 			close_pipes(info->cmd);
// 			close_files(info->cmd);
// 			free_info(info);
// 			save_stdinout(2);
// 			close_std();
// 			exit (1);
// 		}
// 	}
// 	else if (cmd->ag[0] != NULL && (cmd->ag[0] && cmd->ag[0][0]))
// 	{
// 		env_child = env_env_tostrs(info->env);
// 		cmd->cmd_path = command_path(cmd->ag, info->env);
// 		if (cmd->cmd_path != NULL)
// 		{
// 			execve(cmd->cmd_path, cmd->ag, env_child); 
// 				perror("exec failed ");
// 		}
// 		free_strs(env_child);
// 		free_info(info);
// 		save_stdinout(2);
// 		close_std();
// 		exit (errno);
// 	}
	// if (is_builtin(cmd) == 1)
	// {
	// 	if (exec_builtin(cmd, info) == 1)
	// 	{
	// 		close_pipes(info->cmd);
	// 		close_files(info->cmd);
	// 		free_info(info);
	// 		save_stdinout(2);
	// 		close_std();
	// 		exit (1);
	// 	}
	// }
	// else if (cmd->ag[0] != NULL && (cmd->ag[0] && cmd->ag[0][0]))
	// {
	// 	env_child = env_env_tostrs(info->env);
	// 	cmd->cmd_path = command_path(cmd->ag, info->env);
	// 	if (cmd->cmd_path != NULL)
	// 	{
	// 		execve(cmd->cmd_path, cmd->ag, env_child); 
	// 			perror("exec failed ");
	// 	}
	// 	free_strs(env_child);
	// 	free_info(info);
	// 	save_stdinout(2);
	// 	close_std();
	// 	exit (errno);
	// }
// 	free_info(info);
// 	save_stdinout(2);
// 	close_std();
// 	exit (EXIT_SUCCESS);
// }

// int	execute(t_info *info) //20220717 ok
// {
// 	info->error_n = open_files(info->cmd);
// 	save_stdinout(1);
// 	if (info->size == 1 && is_builtin(info->cmd) == 1)
// 	{
// 		if (info->cmd->fdin < 0 || info->cmd->fdout < 0)
// 			return (errno);
// 		// save_stdinout(1);
// 		if (dup_filefds(info->cmd, info) == 1)
// 		{
// 			close_files(info->cmd);
// 			return (errno);
// 		}
// 		if (exec_builtin(info->cmd, info) == 1)
// 		{
// 			close_files(info->cmd);
// 			return (1);
// 		}
// 		close_files(info->cmd);
// 		save_stdinout(2);
// 	}
// 	else
// 	{
// 		if (open_pipes(info->cmd, info) == 1)
// 			return (errno);
// 		return(pipex(info->cmd, info));
// 	}
// 	return (0);
// }

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


/** 20220728 save child before*/
	// env_child = env_env_tostrs(info->env);
	// dup_pipefds(cmd, info);	// 
	// dup_filefds(cmd, info);	// close_files(info->cmd);
	// close_pipes_files(info->cmd);
	// if (cmd->ag[0] == NULL || (cmd->ag[0] && !cmd->ag[0][0]))
	// 	freeinfo_exit(EXIT_SUCCESS, info);
	// // {
	// // 	free_info(info);
	// // 	exit (EXIT_SUCCESS);
	// // }
	// else if (is_builtin(cmd) == 1)
	// {
	// 	if (exec_builtin(cmd, info) == 1)
	// 		freeinfo_exit(EXIT_FAILURE, info);
	// 	// {
	// 	// 	free_info(info);
	// 	// 	exit (EXIT_FAILURE);
	// 	// }
	// }
	// else
	// {
	// 	cmd->cmd_path = command_path(cmd->ag, info->env);
	// 	execve(cmd->cmd_path, cmd->ag, env_child); // if (execve(cmd->cmd_path, cmd->ag, info->env) == -1)
	// 	perror("exec failed ");
	// 	freeinfo_exit(EXIT_FAILURE, info);
	// 	// free_info(info);
	// 	// exit (EXIT_FAILURE);
	// }
	// free_info(info);
	// exit (EXIT_SUCCESS);