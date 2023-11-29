/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:52:06 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/29 15:25:25 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*create_export(char *new_s, int is_export)
{
	t_export	*new;
	char		*k_v[2];

	new = malloc(sizeof(t_export));
	if (!new)
		exit_shell(1, "unable to allocate space");
	if (!*new_s && !ft_perror("export: `\': not a valid identifier"))
		return (NULL);
	ft_split_export(new_s, k_v);
	new->key = k_v[0];
	new->value = k_v[1];
	if (!new->key)
	{
		free(new->key);
		if (new->value)
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
	t_export	*cur;

	new = create_export(new_exp, is_export);
	if (!new)
		return (NULL);
	if (!*first)
	{
		*first = new;
		return (*first);
	}
	cur = *first;
	if (cur->next && ft_strcmp(cur->next->key, new->key) >= 0)
	{
		(*first)->prev = new;
		new->next = *first;
		*first = new;
		return (*first);
	}
	while (cur->next && ft_strcmp(cur->next->key, new->key) < 0)
		cur = cur->next;
	if (cur->next)
		cur->next->prev = new;
	new->next = cur->next;
	cur->next = new;
	new->prev = cur;
	return (*first);
}

t_export	*export_remove(t_export **first, t_export *to_remove)
{
	t_export	*tmp;

	if (!first || !*first || !to_remove)
		return (NULL);
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
	return (*first);
}

t_export	*export_find(t_export *first, char *key)
{
	while (first)
	{
		if (!ft_strcmp(first->key, key))
			return (first);
		first = first->next;
	}
	return (NULL);
}

t_export	*export_modify(t_export **first, char *new)
{
	t_export	*tmp;
	char		*k_v[2];

	if (!*new && !ft_perror("export: `\': not a valid identifier"))
		return (NULL);
	ft_split_export(new, k_v);
	tmp = export_find(*first, k_v[0]);
	if (!tmp)
	{
		free(k_v[0]);
		free(k_v[1]);
		return (export_add(first, new, 1));
	}
	if (k_v[1])
	{
		free(tmp->value);
		tmp->value = k_v[1];
	}
	free(k_v[0]);
	if (!tmp->value)
		return (NULL);
	return (*first);
}
