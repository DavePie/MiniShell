/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:16:39 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/23 14:29:57 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "list_utils.h"
#include "minishell.h"
#include "run_command.h"

int	ft_is_star(t_token *token)
{
	if (token->is_string == 0 && ft_strchr(token->token, '*'))
		return (1);
	return (0);
}

int	is_wildcard(t_token *token)
{
	int	is_next;
	int	found_star;

	is_next = 1;
	found_star = 0;
	while (token && is_next && !found_star)
	{
		if (!token->next || !token->next->adj_prev)
			is_next = 0;
		if (ft_is_star(token))
			found_star = 1;
		token = token->next;
	}
	return (found_star);
}

int	ft_search_substr(char *str, char *substr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i + j] == substr[j] && str[i + j] && substr[j])
			j++;
		if (!substr[j])
			return (i);
		j = 0;
		i++;
	}
	return (-1);
}

int	ft_match_last(char *str, char *substr)
{
	int	i;
	int	j;

	i = ft_strlen(str);
	j = ft_strlen(substr);
	if (j > i)
		return (0);
	while (j >= 0)
	{
		if (str[i] != substr[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

int	match_wildcard(t_token *token, char *str)
{
	int	is_matching;

	is_matching = 1;
	if (!ft_is_star(token) && ft_search_substr(str, token->token) != 0)
		is_matching = 0;
	else if (!ft_is_star(token))
		str += ft_strlen(token->token);
	token = token->next;
	while ((token && token->adj_prev) && (token->next && token->next->adj_prev)
		&& is_matching)
	{
		if (!ft_is_star(token) && ft_search_substr(str, token->token) < 0)
			is_matching = 0;
		else if (!ft_is_star(token))
			str += ft_search_substr(str, token->token)
				+ ft_strlen(token->token);
		token = token->next;
	}
	if (is_matching && (token && token->adj_prev) && !ft_is_star(token)
		&& !ft_match_last(str, token->token))
		is_matching = 0;
	return (is_matching);
}

t_token	*get_matching_elems(t_token *token)
{
	DIR				*dir;
	struct dirent	*elem;
	t_token			*new_list;

	new_list = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	elem = readdir(dir);
	while (elem)
	{
		if (match_wildcard(token, elem->d_name))
			t_add_back(&new_list, t_new(ft_strdup(elem->d_name), 1));
		elem = readdir(dir);
	}
	closedir(dir);
	return (new_list);
}

t_token	*replace_wildcard(t_token **first, t_token *prev, t_token *cur)
{
	t_token	*new_list;

	new_list = get_matching_elems(cur);
	if (!new_list)
	{
		while (cur->next && cur->next->adj_prev)
			cur = cur->next;
		return (cur->next);
	}
	t_del(first, prev);
	while ((prev && prev->next && prev->next->adj_prev)
		|| (!prev && (*first) && (*first)->adj_prev))
		t_del(first, prev);
	if (prev && t_insert(prev, new_list))
		return (*first);
	if (*first)
		prev = *first;
	*first = new_list;
	cur = *first;
	while (cur->next)
		cur = cur->next;
	if (*first)
		cur->next = prev;
	return (*first);
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
