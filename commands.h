/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:05:34 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/21 14:22:28 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H
# define OUTPUT_PIPE -2
# define OUTPUT_STD -3
typedef struct s_com
{
	char	**args;
	char	**env;
	int		input_fd;
	int		output_fd;
}	t_com;

int	exec_commands(t_token **first, char **envp);

#endif