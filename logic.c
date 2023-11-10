/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:27:39 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/10 16:10:11 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "logic.h"
#include "utils.h"

// temp function TO REMOVE
int	run(char *str, int start, int end)
{
	int temp = start;
	printf("ran: |");
	while (start < end)
	{
		printf("%c", str[start]);
		start++;
	}
	printf("| (%d)\n", (end - temp) % 2);
	return ((end - temp) % 2);
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

int	is_logic(char *str, int i)
{
	const char	*vals[5] = {"&&", "(", ")", "||", 0};
	int			j;
	int			back;

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

	while (is_logic(str, start))
		start++;
	i = start;
	while (str[i] && (instr(str, i) || !is_logic(str, i)))
	{
		//printf("%c is valid\n", str[i]);
		//printf("%d %d\n", instr(str, i), !is_logic(str, i));
		i++;
	}
	return (run(str, start, i));
}

int	get_next_command(char *str, char *op, int start)
{
	int	depth;
	int	i;

	while (is_logic(str, start))
		start++;
	i = start;
	depth = 0;
	while (str[i] && (depth || instr(str, i) || !str_at(str, i, op)))
	{
		if (instr(str, i))
			continue ;
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
	int	i;
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
		next_i++;
	}
	return (0);
}
