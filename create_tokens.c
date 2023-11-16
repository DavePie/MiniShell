/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:46:12 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/16 14:12:43 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "minishell.h"
#include "utils.h"
#include "utils_shell.h"
#include "list_utils.h"
#include "libft.h"

int	add_token_split(t_token **list, char *s)
{
	int		i;
	t_token	*ans;
	int		is_str;

	i = 0;
	is_str = (*s == '"' || *s == '\'');
	if ((*s == '|' || *s == '<' || *s == '>'))
	{
		i = 1 + (*s == s[1]);
		ans = t_add_back(list, t_new(ft_substr(s, 0, i), 0));
		return (i);
	}
	while (is_str && s[i] && s[i] != *s)
		i++;
	while (!is_str && s[i]
		&& !is_s(s[i]) && !ft_strchr("$\"'|><", s[i]))
		i++;
	t_add_back(list, t_new(ft_substr(s, is_str, i - 2 * is_str), is_str));
	return (i);
}

t_token	**split_args(char *input)
{
	int		i;
	t_token	**first;
	int		prev;
	int		is_special;

	i = 0;
	first = malloc(sizeof(t_token *));
	if (!input || !first)
		return (0);
	*first = 0;
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
		t_get_last(*first)->adj_prev = (!prev && is_special);
	}
	return (first);
}

void	merge_tokens(t_token **first)
{
	t_token	*cur;
	int	l;

	cur = *first;
	while (cur)
	{
		l = ft_strlen(cur->token);
		while (cur->next && cur->next->adj_prev)
			l += ft_strlen(cur->token);
	}
}