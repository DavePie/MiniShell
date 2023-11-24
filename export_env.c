/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:52:06 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/24 14:01:39 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*create_export(char *new, int is_export)
{
	t_export	*new;

	new = malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	new->key = ft_strndup(new, ft_strchr(new, '=') - new);
	new->value = ft_strdup(ft_strchr(new, '=') + 1);
	if (!new->key || !new->value)
	{
		free(new->key);
		free(new->value);
		free(new);
		return (NULL);
	}
	new->is_export = is_export;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_export	*export_add(t_export **first, char *new_exp, int is_export)
{
	t_export	*new;
	t_export	*tmp;

	new = create_export(new_exp, is_export);
	if (!new)
		return (NULL);
	if (!*first)
	{
		*first = new;
		return (*first);
	}
	tmp = *first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (*first);
}

t_export	*export_remove(t_export **first, t_export *to_remove)
{
	t_export	*tmp;

	if (!first || !*first || !to_remove)
		return ;
	if (*first == to_remove)
	{
		*first = to_remove->next;
		if (*first)
			(*first)->prev = NULL;
	}
	else
	{
		tmp = to_remove->prev;
		tmp->next = to_remove->next;
		if (to_remove->next)
			to_remove->next->prev = tmp;
	}
	free(to_remove->key);
	free(to_remove->value);
	free(to_remove);
}

char	*export_find(t_export *first, char *key)
{
	while (first)
	{
		if (!ft_strcmp(first->key, key))
			return (first->value);
		first = first->next;
	}
	return (NULL);
}

t_export	*export_modify(t_export **first, char *key, char *value)
{
	t_export	*tmp;

	tmp = export_find(first, key);
	if (!tmp)
		return (export_add(first, create_export(key, value, 1)));
	free(tmp->value);
	tmp->value = ft_strdup(value);
	if (!tmp->value)
		return (NULL);
	return (first);
}
