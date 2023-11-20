/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:05:34 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/20 15:55:20 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

typedef struct s_com
{
	char	*cmd;
	char	**args;
	char	**env;
	int		input_fd;
	int		output_fd;
}	t_com;
#endif