/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:15:45 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/25 21:51:31 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_heredoc(char *heredoc, t_cmd *cmd)
// {
// 	char	*tmpinput;
// 	char	*tmpglobal;
// 	char	*tmp;

// 	tmpglobal = NULL;
// 	while (1)
// 	{
// 		tmpinput = readline("> ");
// 		if (tmpinput == NULL)
// 			return (0);
// 		else if (ft_strcmp(tmpinput, heredoc) == 0)
// 		{
// 			ft_putstr_fd(tmpglobal, cmd->in);
// 			free (tmpinput);
// 			free(tmpglobal);
// 			break;
// 		}
// 		else
// 		{
// 			tmp = ft_strjoin(tmpglobal, tmpinput);
// 			free (tmpglobal);
// 			free (tmpinput);
// 			tmpglobal = tmp;
// 		}
// 	}
// 	return (1);
// 	// voir parsing pour la ligne....
// }