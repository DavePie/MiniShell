/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:48:32 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/30 16:26:56 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_shell.h"
#include "minishell.h"
#include "utils.h"
#include "libft.h"

int	fdwrite(int fd, char *s)
{
	return (write(fd, s, ft_strlen(s)));
}

int	ewrite(char *s)
{
	fdwrite(2, "minishell: ");
	fdwrite(2, s);
	fdwrite(2, "\n");
	return (0);
}

int	e_token_write(char *s, char *expec)
{
	fdwrite(2, "minishell: ");
	fdwrite(2, "syntax error near ");
	fdwrite(2, expec);
	fdwrite(2, " token `");
	fdwrite(2, s);
	fdwrite(2, "'\n");
	return (0);
}

int	ft_perror(char *mess)
{
	fdwrite(2, "minishell: ");
	perror(mess);
	return (0);
}

int	exit_shell(int code, char *error)
{
	if (error)
		ewrite(error);
	else
		printf("exit\n");
	clear_history();
	exit(code);
}
