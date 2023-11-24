/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:48:32 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/24 11:04:01 by dvandenb         ###   ########.fr       */
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

int	e_file_write(char *file)
{
	fdwrite(2, "minishell: ");
	fdwrite(2, file);
	fdwrite(2, ": No such file or directory\n");
	return (-1);
}

int	exit_shell(int code)
{
	clear_history();
	exit(code);
}
