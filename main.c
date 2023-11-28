/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:35:09 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/28 16:19:23 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logic.h"
#include "pipe.h"
#include "verify.h"
#include "history.h"
#include "minishell.h"
#include "utils_shell.h"
#include <termios.h>

int	g_sig = 0;

void	handle_ctrlc(int val)
{
	if (val != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char *av[], char **envp)
{
	struct termios	termios_new;
	t_data			d;

	(void)ac, (void)av;
	d = (t_data){.exports = create_list(envp)};
	tcgetattr(0, &termios_new);
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_new);
	signal(SIGINT, handle_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		d.input = ft_read_line();
		if (!d.input || !strcmp(d.input, "exit"))
			exit_shell(0, 0);
		if (verify_input(d.input))
			run_all_commands(&d, envp);
		signal(SIGINT, handle_ctrlc);
		free(d.input);
	}
	return (0);
}
