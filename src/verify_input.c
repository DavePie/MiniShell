/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:13:17 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/30 15:44:19 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "logic.h"
#include "utils_shell.h"
#include "libft.h"
#include "minishell.h"

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
	const char	*vals[23][2]
		= {{"&&", "("}, {"||", "("}, {")", "||"},
	{")", "&&"}, {"(", "("}, {")", ")"}, {"|", "<"},
	{"|", "<<"}, {"|", ">"}, {"|", ">>"}, {"&&", "<"},
	{"&&", "<<"}, {"&&", ">"}, {"&&", ">>"}, {"||", "<"},
	{"||", "<<"}, {"||", ">"}, {"||", ">>"}, {"(", "<"},
	{"(", "<<"}, {"(", ">"}, {"(", ">>"}, {0}};
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

char	*verify_special_characters(char *s, int i, int j)
{
	if (!s[i])
		return (0);
	while (is_s(s[i]))
		i++;
	j = i;
	if (is_special(s, i))
		j += ft_strlen(is_special(s, i));
	while (is_s(s[j]))
		j++;
	while (s[j] && j < (int)ft_strlen(s))
	{
		if (is_special(s, j) && !instr(s, i)
			&& !is_expection(is_special(s, i), is_special(s, j)))
			return (is_special(s, j));
		i = j;
		while (s[i] && !is_special(s, i))
			i++;
		j = i + ft_strlen(is_special(s, i));
		while (j && j < (int)ft_strlen(s) && is_s(s[j]))
			j++;
	}
	return (0);
}
