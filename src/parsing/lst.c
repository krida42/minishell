#include "minishell.h"

static t_cmd	*new_cmd(char *properties[])
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->ag = properties[CMD_AG];
	cmd->in = properties[CMD_IN];
	cmd->out = properties[CMD_OUT];
	cmd->append = properties[CMD_APPEND];
	cmd->heredoc = properties[CMD_HEREDOC];
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

void	add_back(t_cmd **cmd, char *properties[])
{
	t_cmd	*last;

	if (!*cmd)
	{
		*cmd = new_cmd(properties);
		return ;
	}
	last = get_last(*cmd);
	last->next = new_cmd(properties);
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
