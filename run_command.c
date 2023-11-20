/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:07:11 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/20 11:16:01 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "convert_env.h"
#include "minishell.h"

void	print_tokens(t_token *cur)
{
	while (cur)
	{
		printf("[%s](s:%d)(ad:%d), ",
			cur->token, cur->is_string, cur->adj_prev);
		cur = cur->next;
	}
	printf("\n");
}


int	run(char *str, int start, int end, char **envp)
{
	char	*input;
	t_token	**f_list;
	t_token	*cur;

	f_list = malloc(sizeof(t_token *));
	input = ft_substr(str, start, end - start);
	f_list = split_args(input);
	print_tokens(*f_list);
	
	ft_convert_envs(f_list, envp);
	print_tokens(*f_list);
	
	merge_tokens(*f_list, 0);
	print_tokens(*f_list);
	
	convert_wildcards(*f_list);
	print_tokens(*f_list);
	
	merge_tokens(*f_list, 1);
	print_tokens(*f_list);
	
	return ((start - end) % 2);
}