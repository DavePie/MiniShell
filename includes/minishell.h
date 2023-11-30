/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:44:56 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/30 15:57:27 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "structs.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include "export_env.h"
# include "commands.h"
# include "list_utils.h"
# include "pipe.h"
# include "utils_shell.h"
# include "convert_env.h"
# include "logic.h"
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

void	rl_replace_line(const char *c, int d);

#endif