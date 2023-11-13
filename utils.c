/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:25:21 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/13 11:48:48 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s, char *r)
{
	while (*s && *r && *s == *r)
	{
		s++;
		r++;
	}
	return ((unsigned char)*s - (unsigned char)*r);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}


int	instr(char *s, int i)
{
	char	cur;

	cur = 0;
	while (*s && i)
	{
		i--;
		if (*s == '"' || *s == '\'')
		{
			if (cur == *s)
				cur = 0;
			else if (!cur)
				cur = *s;
		}
		s++;
	}
	return (cur);
}

int	str_at(char *str, int index, char *input)
{
	int	i;

	i = 0;
	while (str[index + i] && input[i]
		&& str[index + i] == input[i])
		i++;
	return (!input[i]);
}

int	is_s(char c)
{
	return (c == ' ' || c == '\t');
}
