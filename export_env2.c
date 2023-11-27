/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:43:31 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/27 10:12:50 by alde-oli         ###   ########.fr       */
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
	k_v[0] = ft_strndup(new, ft_strchr(new, '=') - new);
	k_v[1] = ft_strdup(ft_strchr(new, '=') + 1);
	if (k_v[1][0] == '\"')
		k_v[1] = ft_strtrim(k_v[1], "\"");
	else if (k_v[1][0] == '\'')
		k_v[1] = ft_strtrim(k_v[1], "\'");
}
