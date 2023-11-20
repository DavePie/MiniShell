/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:07:55 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/20 12:27:26 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_COMMAND_H
# define RUN_COMMAND_H

void	print_tokens(t_token *cur);

int	run(char *str, int start, int end, char **envp);

#endif