/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:43:31 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/28 13:48:43 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*create_list(char **env)
{
	t_export	*first;
	int			i;

	i = 0;
	first = NULL;
	while (env[i])
	{
		if (!export_add(&first, env[i], 1))
			return (NULL);
		i++;
	}
	return (first);
}

t_export	*export_clear(t_export **first)
{
	t_export	*tmp;

	while (*first)
	{
		tmp = *first;
		*first = (*first)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	return (NULL);
}

void	ft_split_export(char *new, char **k_v)
{
	k_v[0] = ft_strndup(new, ft_strchr(new, '=') - new);//unprotected malloc
	k_v[1] = ft_strdup(ft_strchr(new, '=') + 1);//unprotected malloc
	if (k_v[1][0] == '\"')
		k_v[1] = ft_strtrim(k_v[1], "\"");//mem leaks and unprotected malloc
	else if (k_v[1][0] == '\'')
		k_v[1] = ft_strtrim(k_v[1], "\'");//mem leak and unprotected malloc
}
