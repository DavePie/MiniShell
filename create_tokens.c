/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:46:12 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/16 13:13:40 by dvandenb         ###   ########.fr       */
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
	int	i;

	i = 0;
	while ((*s == '"' || *s == '\'') && s[i] && s[i] != *s)
		i++;
	while (*s != '"' && *s != '\'' && s[i]
		&& !is_s(s[i]) && !ft_strchr("$\"'", s[i]))
		i++;
	t_add_back(list, t_new(ft_substr(s, 0, i)));
	return (i);
}

t_token	**split_args(char *input)
{
	int		i;
	t_token	**first;
	int		prev;

	i = 0;
	first = malloc(sizeof(t_token *));
	if (!input)
		return (0);
	while (input[i])
	{
		prev = 0;
		while (is_s(input[i]) && ++prev)
			i++;
		if (!input[i])
			break ;
		i += add_token_split(first, input + i);
		t_get_last(*first)->adj_prev = !prev;
	}
	return (first);
}
