/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:07:11 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/23 14:30:29 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert_env.h"
#include "minishell.h"
#include "wildcards.h"
#include "create_tokens.h"
#include "libft.h"
#include "commands.h"
#include "list_utils.h"

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
	int		return_val;

	input = ft_substr(str, start, end - start);
	//printf("input string: %s", input);
	//printf("split args:\n");
	f_list = split_args(input);
	//printf("add env:\n");
	ft_convert_envs(f_list);
	//print_tokens(*f_list);
	//printf("pre-merge wildcard:\n");
	merge_tokens(*f_list, 0);
	//print_tokens(*f_list);
	//printf("wildcard:\n");
	convert_wildcards(f_list);
	//print_tokens(*f_list);
	//printf("final merge:\n");
	merge_tokens(*f_list, 1);
	//print_tokens(*f_list);
	free(input);
	return_val = 0;
	return_val = (exec_commands(f_list, envp));
	t_clear(f_list);
	free(f_list);
	return (return_val);
}
