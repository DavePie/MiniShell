/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:44:56 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/14 11:06:51 by dvandenb         ###   ########.fr       */
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
# define STR1 = 1
# define STR2 = 2
# define NAME = "minishell"


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