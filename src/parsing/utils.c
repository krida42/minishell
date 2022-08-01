/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:42:04 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 19:58:43 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int	strs_len(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
		i++;
	return (i);
}

char	**strs_insert(char ***strs, const char *s)
{
	int		new_len;
	char	**new_strs;
	int		i;

	new_len = strs_len(*strs) + 1;
	new_strs = malloc(sizeof(char *) * (new_len + 1));
	if (!*strs)
	{
		new_strs[0] = ft_strdup(s);
		new_strs[1] = NULL;
		*strs = new_strs;
		return (new_strs);
	}
	i = -1;
	while ((*strs)[++i])
		new_strs[i] = (*strs)[i];
	new_strs[i++] = ft_strdup(s);
	new_strs[i] = NULL;
	free(*strs);
	*strs = new_strs;
	return (new_strs);
}

char	**strs_remove(char ***strs, int index)
{
	int		len;
	char	**new_strs;
	int		i;
	int		k;

	if (!*strs)
		exit(printf("DANGER - strs_remove - *strs is NULL"));
	len = strs_len(*strs);
	if (index >= len || index < 0)
		exit(printf("DANGER - strs_remove - index out of range"));
	new_strs = malloc(sizeof(char *) * len);
	i = -1;
	k = 0;
	while ((*strs)[++i])
	{
		if (i != index)
			new_strs[k++] = (*strs)[i];
		else
			free((*strs)[i]);
	}
	new_strs[k] = NULL;
	free(*strs);
	*strs = new_strs;
	return (new_strs);
}

int	isinset(char c, const char *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	**free_strs(char	**strs)
{
	int	i;

	i = -1;
	if (!strs)
		return (NULL);
	while (strs[++i])
		free(strs[i]);
	free(strs);
	return (NULL);
}
