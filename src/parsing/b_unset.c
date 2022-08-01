/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:07:39 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 19:07:40 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(t_info *info, char **args)
{
	while (*args)
	{
		if (env_get_ptr(info->env, *args))
			env_rm(&info->env, *args);
		args++;
	}
	return (0);
}
