/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:27:39 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/17 10:40:07 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logic.h"
#include "utils.h"
#include "libft.h"
#include "tokens.h"
#include "create_tokens.h"
// temp function TO REMOVE!!
// norminette error here on purpose!
#include <stdio.h>

int	run(char *str, int start, int end)
{
	char	*input;
	t_token	**f_list;
	t_token	*cur;

	f_list = malloc(sizeof(t_token *));
	input = ft_substr(str, start, end - start);
	f_list = split_args(input);
	cur = *f_list;
	while (cur)
	{
		printf("[%s](s:%d)(ad:%d), ",
			cur->token, cur->is_string, cur->adj_prev);
		cur = cur->next;
	}
	return ((start - end) % 2);
}

int	is_logic(char *str, int i)
{
	const char	*vals[5] = {"&&", "(", ")", "||", 0};
	int			j;

	j = 0;
	while (vals[j])
	{
		if (i > 1 && ft_strlen(vals[j]) == 2
			&& str_at(str, i - 1, (char *)vals[j]))
			return (1);
		if (str_at(str, i, (char *)vals[j]))
			return (1);
		j++;
	}
	return (0);
}

int	run_command_at(char *str, int start)
{
	int	i;

	while (is_logic(str, start) || is_s(str[start]))
		start++;
	i = start;
	while (str[i] && (instr(str, i) || !is_logic(str, i)))
		i++;
	return (run(str, start, i));
}

int	get_next_command(char *str, char *op, int i)
{
	int	depth;

	while (is_logic(str, i) || is_s(str[i]))
		i++;
	depth = 0;
	while (str[i] && (depth || instr(str, i) || !str_at(str, i, op)))
	{
		if (instr(str, i))
		{
			i++;
			continue ;
		}
		if (str[i] == '(')
			depth++;
		if (str[i] == ')' && depth)
			depth--;
		i++;
	}
	if (!str[i])
		return (-1);
	return (i);
}

int	run_all_commands(char *str)
{
	int	cur;
	int	next_i;

	cur = run_command_at(str, 0);
	next_i = 0;
	while (next_i != -1)
	{
		if (cur)
			next_i = get_next_command(str, "&&", next_i);
		else
			next_i = get_next_command(str, "||", next_i);
		if (next_i == -1)
			break ;
		cur = run_command_at(str, next_i);
	}
	return (0);
}
