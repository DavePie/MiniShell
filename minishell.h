/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:44:56 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/08 15:56:03 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define STR1 = 1
# define STR2 = 2

/**
 * @brief struct containing the token and if it is a pipe/redir
 * @note We need this since a string can't become a pipe/redir.
 */
typedef struct s_token
{
	int		is_special;
	char	*token;
}	t_token;

/**
 * @brief Returns if the selected index is within quotes
 * emphasis on the outermost quotes
 * 
 * @param s the string to search
 * @param i the index
 * @return int 1 if single quote, 2 if double quote
 */
int		instr(char *s, int i);

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
int		eval_groups(char *s, int start, int end);

/**
 * @brief Given a string without () && ||, execute the command
 * 
 * @param s 
 * @param start 
 * @param end 
 * @return int 
 */
int		eval_str(char *s, int start, int end);

/*
!caution! two adjacent strings are the same token
	but don't get spaces removed, similar to strings
	this is due to the described order
!caution! exported variables can contain wildcards
!caution! while strings can become commands,
	strings can't become redirections/pipes
	
*/

/**
 * @brief Given a substring denoted by start, end, extract the tokens
 * determined by quotes, spaces/tabs, env vars, and wildcards IN THAT ORDER!
 * @param s intput string
 * @param start 
 * @param end 
 * @return t_token* NULL ternimated array of tokens
 */
t_token	*get_tokens(char *s, int start, int end);

/**
 * @brief Get the file names from a wildcard
 * 
 * @param wcard the card to match to
 * @param dir the directory to search in
 * @return char** a NULL terminated array of matching file names
 */
char	**get_wildcard(char *wcard, char *dir);

/**
 * @brief Given a wildcard and a string, say if it matches 
 * 
 * @param wcard the wildcard
 * @param s the string
 * @return int (if it matches)
 */
int		match_wildcard(char *wcard, char *s);

/*
Todo: pipes redir execute
*/

#endif