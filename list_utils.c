/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:01:15 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/16 12:29:02 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "minishell.h"

t_token	*t_new(char *token)
{
	t_token	*ans;

	ans = (t_token *)malloc(sizeof(*ans));
	if (ans)
	{
		ans->token = token;
		ans->next = 0;
	}
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

void	t_del(t_token **begin_list, t_token *prev, t_token *cur)
{
	if (prev)
		prev->next = prev->next->next;
	else
		*begin_list = (*begin_list)->next;
	free(cur->token);
	free(cur);
}

void	t_add_back(t_token **lst, t_token *new_t)
{
	t_token	*cur;

	if (!*lst)
	{
		*lst = new_t;
		return ;
	}
	cur = *lst;
	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = new_t;
}
