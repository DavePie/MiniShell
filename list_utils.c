/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:01:15 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/23 14:29:46 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*t_new(char *token, int isstr)
{
	t_token	*ans;

	ans = (t_token *)malloc(sizeof(*ans));
	if (ans)
		*ans = (t_token){.token = token, .is_string = isstr};
	return (ans);
}

t_token	*t_get_last(t_token *start)
{
	while (start && start->next)
		start = start->next;
	return (start);
}

void	t_del(t_token **begin_list, t_token *prev)
{
	t_token	*cur;

	if (!prev && begin_list && *begin_list)
	{
		cur = (*begin_list)->next;
		free(*begin_list);
		*begin_list = cur;
	}
	if (!prev)
		return ;
	cur = prev->next;
	if (!cur)
		return ;
	prev->next = prev->next->next;
	if (cur->token)
		free(cur->token);
	cur->token = 0;
	free(cur);
}

t_token	*t_add_back(t_token **lst, t_token *new_t)
{
	t_token	*cur;

	if (!*lst)
	{
		*lst = new_t;
		return (new_t);
	}
	cur = *lst;
	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = new_t;
	return (new_t);
}

void	t_clear(t_token **lst)
{
	t_token	*cur;
	t_token	*temp;

	if (!lst)
		return ;
	cur = *lst;
	while (cur)
	{
		temp = cur;
		cur = cur->next;
		free(temp->token);
		free(temp);
	}
	*lst = 0;
}
