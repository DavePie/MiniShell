/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:03:47 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/10 12:50:44 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
/*
!caution! two adjacent strings are the same token
	but don't get spaces removed, similar to strings
	this is due to the described order
!caution! exported variables can contain wildcards
!caution! while strings can become commands,
	strings can't become redirections/pipes
	
*/

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
 * @brief Given a substring denoted by start, end, extract the tokens
 * determined by quotes, spaces/tabs, env vars, and wildcards IN THAT ORDER!
 * @note tokens must also remain in the order they are read
 * @note uses the get_tokens function
 * @param s intput string
 * @param start 
 * @param end 
 * @return t_token* NULL ternimated array of tokens
 */
t_token	*get_tokens_all(char *s, int start, int end);

/**
 * @brief Given a single space/tab delimited string, return an array of tokens
 * @param s string, with bounds determined by:
 * @param start index
 * @param end index
 * @return t_token* 
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

/**
 * @brief Given a string without () && ||, execute the command
 * @note this may include pipes, redirs, etc, but is self contained
 * @param s 
 * @param start 
 * @param end 
 * @return int 
 */
int		eval_str(char *s, int start, int end);

#endif