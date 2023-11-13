/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:13:17 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/13 11:56:24 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "logic.h"
#include "utils_shell.h"

int	verify_paranthesis(char *s)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (instr(s, i) && ++i)
			continue ;
		if (s[i] == '(')
			counter++;
		else if (s[i] == ')')
			counter--;
		if (counter < 0)
		{
			ewrite("syntax error near unexpected token `)'");
			return (0);
		}
		i++;
	}
	if (counter > 0)
		ewrite("expected token `)'");
	return (!counter);
}

int	verify_str(char *s)
{
	char	cur;

	cur = 0;
	while (*s)
	{
		if (*s == '"' || *s == '\'')
		{
			if (cur == *s)
				cur = 0;
			else if (!cur)
				cur = *s;
		}
		s++;
	}
	if (cur)
		ewrite("expected closing quote");
	return (!cur);
}

char	*is_special(char *str, int i)
{
	const char	*vals[10]
		= {"&&", "(", ")", "||", "|", "<<", ">>", "<", ">", 0};
	int			j;

	j = -1;
	while (vals[++j])
	{
		if (str_at(str, i, (char *)vals[j]))
			return ((char *)vals[j]);
	}
	return (0);
}

int	is_expection(char *first, char *second)
{
	const char	*vals[7][2]
		= {{"&&", "("}, {"||", "("}, {")", "||"},
	{")", "&&"}, {"(", "("}, {")", ")"}, {0}};
	int			i;

	i = -1;
	while (vals[++i][0] && first && second)
	{
		if (!ft_strcmp(first, (char *)vals[i][0])
			&& !ft_strcmp(second, (char *)vals[i][1]))
			return (1);
	}
	return (0);
}

int	verify_special_characters(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s[i])
		return (1);
	j += ft_strlen(is_special(s, i));
	while (is_s(s[j]))
		j++;
	while (s[j] && j < ft_strlen(s))
	{
		if (is_special(s, j) && !instr(s, i)
			&& !is_expection(is_special(s, i), is_special(s, j)))
			return (0);
		i = j;
		while (s[i] && !is_special(s, i))
			i++;
		j = i + ft_strlen(is_special(s, i));
		while (j < ft_strlen(s) && is_s(s[j]))
			j++;
	}
	return (1);
}

int	verify_edges(char *s)
{
	const char	*edges[8]
		= {"&&", "||", "|", "<<", ">>", "<", ">", 0};
	int			i;
	int			j;
	int			k;

	i = 0;
	k = ft_strlen(s) - 1;
	if (k < 0)
		return (1);
	while (s[i] && is_s(s[i]))
		s++;
	while (k > 0 && s[k] && is_s(s[k]))
		k--;
	j = -1;
	while (edges[++j])
	{
		if (str_at(s, i, (char *)edges[j])
			|| str_at(s, k, (char *)edges[j]))
			return (0);
	}
	return (1);
}

int	verify_paren_logic(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		if (!instr(s, i) && s[i] == '(' && i > 0)
		{
			j = i - 1;
			while (is_s(s[j]) && j > 0 && s[j] != '(')
				j--;
			if (j > 0 && !is_logic(s, j))
				return (0);
		}
		if (!instr(s, i) && s[i] == ')')
		{
			j = i + 1;
			while (s[j] && is_s(s[j]))
				j++;
			if (s[j] && !is_logic(s, j) && s[j] != ')')
				return (0);
		}
		i++;
	}
	return (1);
}

int	verify_input(char *s)
{
	return (verify_special_characters(s) && verify_edges(s)
		&& verify_paranthesis(s) && verify_str(s) && verify_paren_logic(s));
}
