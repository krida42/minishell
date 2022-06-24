#include "minishell.h"

static t_cmd	*new_cmd(char **ag)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->ag = ag;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->append = NULL;
	cmd->heredoc = NULL;
    cmd->cmd_path = NULL;
    cmd->pipefd[0] = -1;
    cmd->pipefd[1] = -1;
    cmd->fdin = -1;
    cmd->fdout = -1;
    cmd->pid = -1;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*get_first(t_cmd *cmd)
{
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}

t_cmd	*get_last(t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	add_back(t_cmd **cmd, char **ag)
{
	t_cmd	*last;

	if (!*cmd)
	{
		*cmd = new_cmd(ag);
		return ;
	}
	last = get_last(*cmd);
	last->next = new_cmd(ag);
	(last->next)->prev = last;
}

int	cmd_size(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}
