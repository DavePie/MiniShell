/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:48:32 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/14 09:09:38 by dvandenb         ###   ########.fr       */
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
	fdwrite(0, "minishell: ");
	fdwrite(0, s);
	fdwrite(0, "\n");
	return (0);
}

int	e_token_write(char *s, char *expec)
{
	fdwrite(0, "minishell: ");
	fdwrite(0, "syntax error near ");
	fdwrite(0, expec);
	fdwrite(0, " token `");
	fdwrite(0, s);
	fdwrite(0, "'\n");
	return (0);
}

int	exit_shell(int code)
{
	clear_history();
	exit(code);
}
