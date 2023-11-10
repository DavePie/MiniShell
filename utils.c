/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:25:21 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/10 15:42:12 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
//#include <utils.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i++])
		;
	return (i - 1);
}

int	ewrite(char *s)
{
	write(0, "minishell: ", ft_strlen("minishell: "));
	write(0, s, ft_strlen(s));
	write(0, "\n", ft_strlen("\n"));
	return (0);
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