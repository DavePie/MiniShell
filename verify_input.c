/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:13:17 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/10 17:30:41 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

int	verify_input(char *s)
{
	return (0);
}

int	verify_paranthesis(char *s)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (instr(s, i))
			continue ;
		if (*s == '(')
			counter++;
		else if (*s == ')')
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
	int			back;

	j = -1;
	while (vals[++j])
	{
		if (str_at(str, i, (char *)vals[j]))
			return (vals[j]);
	}
	return (0);
}

int	is_expection(char *first, char *second)
{
	const char	*vals[4][2]
		= {{"&&", "("}, {"||", "("}, {")", "||"},
	{")", "&&"}, {"(", "("}, {")", ")"}, 0};
	int			i;

	i = -1;
	while (vals[++i])
	{
		if (!ft_strcmp(first, vals[i][0])
			&& !ft_strcmp(second, vals[i][1]))
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
	while (s[i] && !is_special(s, i))
		i++;
	if (!s[i])
		return (1);
	j = i + 1;
	while (is_s(s[j]))
		j++;
	while (s[j])
	{
		if (is_special(s, j) && !is_expection())
	}
	return (1);
}

