/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:40:46 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/20 16:56:29 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"
#include "minishell.h"
#include "commands.h"

/*
File: directly after redir (< file), checked first.
	Files can't become commands. (cat < a < b, a isn't command)
	print can only error once, but still check rest of files
Command: is not before redir.
Pipes: Fake pipe if redir on command
Arg not redir but after command without pipe


*/


/**
 * @brief Get the type object
 * 
 * @param token 
 * @return int 
 */
int	type_t(t_token *token)
{
	if (token->is_string)
		return (0);
	if (!ft_strcmp(token->token, "|"))
		return (PIPE);
	if (!ft_strcmp(token->token, ">"))
		return (OUT);
	if (!ft_strcmp(token->token, ">>"))
		return (OUT_A);
	if (!ft_strcmp(token->token, "<"))
		return (IN);
	if (!ft_strcmp(token->token, "<<"))
		return (IN_D);
	return (0);
}

int	exec_commands(t_token *first)
{
	t_token	*cur;
	t_com	cur_c;
	int		prev;

	cur_c = (t_com){};
	cur = first;
	prev = -1;
	while (cur)
	{
		if (type_t(cur) && type_t(cur) < 4)
			break ; // End command, output to file accordingly
		if (prev > 3)
			break ; // Open file and set fileid
		if (prev == PIPE || prev == -1)
			break ; // Set command
		if (!prev && !type_t(cur))
			break ; // Add arg
		prev = type_t(cur);
		cur = cur->next;
	}
	// end of command, output to stdout
	return (0); // last command output.
}
