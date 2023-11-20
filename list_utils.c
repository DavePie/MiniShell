/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:01:15 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/20 10:25:21 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "minishell.h"

t_token	*t_new(char *token, int isstr)
{
	t_token	*ans;

	ans = (t_token *)malloc(sizeof(*ans));
	if (ans)
		*ans = (t_token){.token = token, .is_string = isstr};
	return (ans);
}

int	t_size(t_token *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
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

	cur = prev->next;
	if (prev)
		prev->next = prev->next->next;
	else
		*begin_list = (*begin_list)->next;
	free(cur->token);
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
