/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:36:13 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/30 18:24:12 by dvandenb         ###   ########.fr       */
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

void	read_sub_env(char **input, t_data *d)
{
	char	*env;

	*input = readline("> ");
	env = ft_get_env(*input, d);
	while (env)
	{
		*input = ft_insert_env(input, env);
		env = ft_get_env(*input, d);
	}
}
