/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:36:13 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/14 12:18:00 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "minishell.h"

char	*ft_read_line(void)
{
	char		*line;

	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	return (line);
}
