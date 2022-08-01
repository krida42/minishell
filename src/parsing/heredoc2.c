/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:07:12 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 20:07:12 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 2);
		exit(130);
	}
}

void	heredoc_sig(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = heredoc_handler;
	sigaction(SIGINT, &sa, NULL);
}
