/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:44:56 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/24 13:48:12 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include "commands.h"
# include "error.h"
# include "export_env.h"
# include "list_utils.h"
# include "pipe.h"
# include "utils_shell.h"
# include "convert_env.h"
# include "export_env.h"
# include "logic.h"
# include "redir.h"
# include "verify.h"
# include "create_tokens.h"
# include "history.h"
# include "minishell.h"
# include "utils.h"
# include "wildcards.h"
# include "libft.h"
# define SINGLE 1
# define DOUBLE 2
# define NAME = "minishell"
# define PIPE 1
# define OUT 2
# define OUT_A 3
# define IN 4
# define IN_D 5

/**
 * @brief struct containing the token and if it is a pipe/redir
 * @note We need this since a string can't become a pipe/redir.
 */
typedef struct s_token
{
	int				is_string;
	char			*token;
	struct s_token	*next;
	int				adj_prev;
}	t_token;

void	rl_replace_line(const char *c, int d);

extern int	g_sig;
/**
 * For evaluating () || &&, commands are always executed left->right
 * However, whether or not a command is executed, and the final return value,
 * is changed by () || &&
 * A recursive approach should work well
 */

/**
 * @brief given a start and end index, evaluate all the groups 
 * 
 * @param s the input
 * @param start start index
 * @param end end index
 * @return int (return value of group)
 */
int		eval_input(char *s);

#endif