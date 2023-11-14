/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:09:36 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/14 11:13:21 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"

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
t_token	*get_tokens(char *s, int start, int end);

char	**get_wildcard(char *wcard, char *dir)
{
	DIR				*directory;
	struct dirent	*elem;
	char			**elems;
	int				n;

	directory = opendir(dir);
	if (!directory)
		return (NULL);
	elem = readdir(directory);
	n = 0;
	while (elem)
	{
		if (match_wildcard(wcard, elem->d_name) == 0)
			n++;
		elem = readdir(directory);
	}
	closedir(directory);
	elems = ft_calloc(n + 1, sizeof(char *));
	if (!elems)
		return (NULL);
	return (get_elems(elems, n, dir, wcard));
}

char	**get_elems(char **elems, int n, char *dir, char *wcard)
{
	struct dirent	*elem;
	DIR				*directory;
	int				i;

	directory = opendir(dir);
	i = 0;
	elem = readdir(directory);
	while (i < n && elem)
	{
		if (match_wildcard(wcard, elem->d_name) == 0)
		{
			elems[i] = ft_strdup(elem->d_name);
			if (!elems[i])
				return (NULL);
			i++;
		}
		elem = readdir(directory);
	}
	elems[i] = NULL;
	closedir(directory);
	return (elems);
}

int	match_wildcard(char *wcard, char *s)
{
	if (*wcard == '*' && !*(wcard + 1))
		return (0);
	if (*wcard == '*')
	{
		wcard++;
		while (*s && *s != *wcard)
			s++;
		if (!*s)
			return (-1);
	}
	while (*s && *wcard && *wcard != '*')
	{
		if (*s != *wcard)
			return (-1);
		s++;
		wcard++;
	}
	return (0);
}

/**
 * @brief Given a string without () && ||, execute the command
 * @note this may include pipes, redirs, etc, but is self contained
 * @param s 
 * @param start 
 * @param end 
 * @return int 
 */
int		eval_str(char *s, int start, int end);
