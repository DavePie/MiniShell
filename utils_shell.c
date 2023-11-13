/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:48:32 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/13 12:39:03 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_shell.h"
#include "minishell.h"
#include "utils.h"

int	ewrite(char *s)
{
	write(0, "minishell: ", ft_strlen("minishell: "));
	write(0, s, ft_strlen(s));
	write(0, "\n", ft_strlen("\n"));
	return (0);
}

int	exit_shell(int code)
{
	clear_history();
	exit(code);
}
