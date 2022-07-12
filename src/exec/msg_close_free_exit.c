/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_close_free_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:02:14 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/01 19:13:10 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msg_close_free_exit(char *str, t_info *info)
{
	perror(str);
	close_pipes(info->cmd);
	close_files(info->cmd);
	ft_free(info);
	exit(EXIT_FAILURE);
}