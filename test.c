/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:35:09 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/21 17:36:55 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logic.h"
#include "main.h"
#include "pipe.h"
#include "history.h"
#include "minishell.h"
#include "utils_shell.h"
#include "tokens.h"

int	g_sig = 0;

void	handle_ctrlc(int val)
{
	if (val != SIGINT)
		return ;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char *av[], char **envp)
{
	char	*input;

	av += ac * 0;
	signal(SIGINT, handle_ctrlc);
	while (1)
	{
		input = ft_read_line();
		if (!input)
			exit_shell(0);
		printf("intput is %d\n", verify_input(input));
		if (verify_input(input))
			run_all_commands(input, envp);
		free(input);
	}
	return (0);
}
