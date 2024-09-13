/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:22:32 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/23 14:30:26 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "list_utils.h"

t_token	*t_replace(t_token **first,
	t_token *prev, t_token *arg, t_token *to_add)
{
	t_token	*next;

	next = t_insert(arg, to_add);
	t_del(first, prev);
	return (next);
}

t_token	*t_insert(t_token *dest, t_token *src)
{
	t_token	*back;

	if (!dest || !src)
		return (0);
	back = dest->next;
	dest->next = src;
	while (dest->next)
		dest = dest->next;
	dest->next = back;
	return (dest);
}
