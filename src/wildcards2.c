/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:21:58 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/23 15:28:30 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "wildcards.h"
#include "libft.h"

int	ft_is_star(t_token *token)
{
	return (token->is_string == 0 && ft_strchr(token->token, '*'));
}

int	is_wildcard(t_token *token)
{
	while (token)
	{
		if (ft_is_star(token))
			return (1);
		if (!token->next || !token->next->adj_prev)
			break ;
		token = token->next;
	}
	return (0);
}

t_token	**convert_wildcards(t_token **list)
{
	t_token	*cur;
	t_token	*prev;

	cur = *list;
	prev = NULL;
	while (cur)
	{
		if (is_wildcard(cur))
			cur = replace_wildcard(list, prev, cur);
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	return (list);
}
