/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:46:12 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/21 07:15:03 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "minishell.h"
#include "utils.h"
#include "utils_shell.h"
#include "list_utils.h"
#include "libft.h"
#include "create_tokens.h"

int	add_token_split(t_token **list, char *s)
{
	int		i;
	t_token	*ans;
	int		is_str;

	ans = NULL;
	if (!ans)
		ans = NULL;
	i = 0;
	is_str = 2 * (*s == '"') + 1 * (*s == '\'');
	if ((*s == '|' || *s == '<' || *s == '>' || *s == '*'))
	{
		i = 1 + (*s == s[1]);
		ans = t_add_back(list, t_new(ft_substr(s, 0, i), 0));
		return (i);
	}
	i++;
	while (is_str && s[i] && (s[i++] != *s))
		;
	while (!is_str && s[i]
		&& !is_s(s[i]) && !ft_strchr("$\"'|><*", s[i]))
		i++;
	t_add_back(list, t_new(ft_substr(s, !!is_str, i - 2 * !!is_str), is_str));
	return (i);
}

t_token	**split_args(char *input)
{
	int		i;
	t_token	**first;
	int		prev;
	int		is_special;
	int		spec_prev;

	spec_prev = 0;
	i = 0;
	first = ft_calloc(1, sizeof(t_token *));
	if (!input || !first)
		return (0);
	while (input[i])
	{
		prev = 0;
		while (is_s(input[i]) && ++prev)
			i++;
		if (!input[i])
			break ;
		i += add_token_split(first, input + i);
		is_special = (!t_get_last(*first)->is_string
				&& ft_strchr("|<>", t_get_last(*first)->token[0]));
		t_get_last(*first)->adj_prev = !prev * !is_special * spec_prev;
		spec_prev = !is_special;
	}
	return (first);
}

int	is_wild_token(t_token *cur)
{
	return (!cur->is_string && cur->token && cur->token[0] == '*');
}

void	merge_str(t_token *cur, int l, int ignore_wild)
{
	t_token	*temp;
	char	*s;

	temp = cur->next;
	s = cur->token;
	cur->is_string = 1;
	cur->token = malloc(sizeof(char) * l + 1);
	ft_strcpy(cur->token, s);
	s = cur->token + ft_strlen(s);
	while (temp && temp->adj_prev && (ignore_wild || !is_wild_token(temp)))
	{
		ft_strcpy(s, temp->token);
		s += ft_strlen(temp->token);
		temp = temp->next;
		t_del(0, cur);
	}
}

void	merge_tokens(t_token *cur, int ignore_wild)
{
	t_token	*temp;
	int		l;
	int		first;

	while (cur)
	{
		l = 0;
		temp = cur;
		first = 1;
		while (temp && (first || temp->adj_prev)
			&& (ignore_wild || !is_wild_token(temp)))
		{
			l += ft_strlen(temp->token);
			temp = temp->next;
			first = 0;
		}
		if (l)
			merge_str(cur, l, ignore_wild);
		cur = cur->next;
	}
}
