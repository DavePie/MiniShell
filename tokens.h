/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:03:47 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/15 11:06:50 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

//need calloc, strlen and strdup

# include <dirent.h>
# include <unistd.h>
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
	int				is_string;
	char			*token;
	struct s_token	*next;
}	t_token;

/**
 * @brief Given a substring denoted by start, end, extract the tokens
 * determined by quotes, env vars, spaces/tabs, and wildcards IN THAT ORDER!
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
t_token	*get_tokens(char *s, int start, int end, char **envp);

/**
 * @brief Get the file names from a wildcard. use "./" for current directory
 * 
 * @param wcard the card to match to
 * @param dir the directory to search in
 * @return char** a NULL terminated array of matching file names
 */
char	**get_wildcard(char *wcard, char *dir);
/**
 * @brief Get the elems object from a wildcard
 * 
 * @param elems 
 * @param n 
 * @param dir 
 * @param wcard 
 * @return char** 
 */
char	**get_elems(char **elems, int n, char *dir, char *wcard);

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