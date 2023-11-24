/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:05:34 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/24 10:56:09 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H
# define OUTPUT_PIPE -2
# define OUTPUT_STD -3
# define NO_INPUT -2
# include "minishell.h"

typedef struct s_com
{
	char	**args;
	char	**env;
	int		i_fd;
	int		o_fd;
}	t_com;

int		exec_commands(t_token **first, char **envp);

void	print_tokens(t_token *cur);

int		run(char *str, int start, int end, char **envp);

int		exec_next_command(t_token **cur, t_com *cmd, int l);

int		type_t(t_token *token);

int		set_cmd_args(t_token *cur, int l, t_com *cur_c);

int		exec_redir(char *delim);

#endif