/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:43:31 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/28 16:12:33 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	**create_list(char **env)
{
	t_export	**first;
	int			i;

	i = 0;
	first = malloc(sizeof(t_export *));
	if (!first)
		exit_shell(1, "unable to allocate space");
	while (env[i])
	{
		if (!export_add(first, env[i], 0))
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
	char	*tmp;

	k_v[0] = ft_strndup(new, ft_strchr(new, '=') - new);
	k_v[1] = ft_strdup(ft_strchr(new, '=') + 1);
	if (!k_v[0] || !k_v[1])
	{
		if (k_v[0])
			free(k_v[0]);
		if (k_v[1])
			free(k_v[1]);
		ft_error("Malloc error.");
	}
	if (k_v[1][0] == '\"' || k_v[1][0] == '\'')
	{
		tmp = ft_strndup(k_v[1] + 1, ft_strlen(k_v[1]) - 2);
		free(k_v[1]);
		k_v[1] = tmp;
		if (!k_v[1])
			ft_error("Malloc error.");
	}
}
