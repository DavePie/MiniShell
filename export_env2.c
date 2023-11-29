/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:43:31 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/29 15:47:20 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	**create_list(char **env)
{
	t_export	**first;
	int			i;

	i = 0;
	first = malloc(sizeof(t_export *));
	*first = 0;
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

static void	handle_allocation_error(char **k_v)
{
	if (k_v[0])
		free(k_v[0]);
	if (k_v[1])
		free(k_v[1]);
	exit(1);
}

static void	handle_quotes(char **k_v)
{
	char	*tmp;

	if (*k_v[1] == '\'' || *k_v[1] == '\"')
	{
		tmp = ft_substr(k_v[1], 1, ft_strlen(k_v[1]) - 2);
		if (!tmp)
			handle_allocation_error(k_v);
		free(k_v[1]);
		k_v[1] = tmp;
	}
}

void	ft_split_export(char *new, char **k_v)
{
	char	*equal_pos;

	equal_pos = ft_strchr(new, '=');
	if (equal_pos)
	{
		k_v[0] = ft_substr(new, 0, equal_pos - new);
		if (!k_v[0])
			handle_allocation_error(k_v);
		if (*(equal_pos + 1))
			k_v[1] = ft_substr(equal_pos + 1, 0, ft_strlen(equal_pos + 1));
		else
			k_v[1] = ft_strdup("");

		if (!k_v[1])
			handle_allocation_error(k_v);
		handle_quotes(k_v);
	}
	else
	{
		k_v[0] = ft_strdup(new);
		k_v[1] = NULL;
		if (!k_v[0])
			handle_allocation_error(k_v);
	}
}
