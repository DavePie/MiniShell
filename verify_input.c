/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:13:17 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/10 13:39:05 by dvandenb         ###   ########.fr       */
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
