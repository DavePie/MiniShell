/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:36:13 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/14 11:43:26 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "minishell.h"

char	*ft_read_line(void)
{
	char		*line;
	int			status;
	const pid_t	p = fork();

	if (p == 0)
	{
		line = readline("minishell$ ");
		//kill()
		exit(0);
	}
	else if (p == -1)
	{
		printf("error\n");
		exit(1);
	}
	while (!g_sig)
		kill(0, SIGKILL);
	waitpid(p, &status, 0);
	// if (line && *line)
	// 	add_history(line);
	return "";
}
