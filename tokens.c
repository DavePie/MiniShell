/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:09:36 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/14 14:47:46 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

char	ft_is_env(char *s, int start, int end)
{
	int		i;
	int		j;
	char	*exp;

	i = 0;
	while (start < end && s[start] != ' ' && s[start]
		!= '\t' && s[start] != '$')
		start++;
	if (s[start] != '$')
		return (NULL);
	while (start < end && s[start + i] != ' ' && s[start + i] != '\t')
		i++;
	exp = ft_calloc(i + 1, sizeof(char));
	if (!exp)
		return (NULL);
	while (start < end && s[start] != ' ' && s[start] != '\t')
	{
		exp[i] = s[start + i];
		i++;
	}
	return (exp);
}

char	*ft_

int	ft_is_wildcard(char *s, int start, int end)
{
	while (start < end && s[start] != ' ' && s[start] != '\t')
	{
		if (s[start] == '*')
			return (1);
		start++;
	}
	return (0);
}

int	ft_get_type(char *s);

t_token	*ft_free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->s);
		free(tokens);
		tokens = tmp;
	}
	return (NULL);
}

char	*ft_extract_token(char *s, int *start, int end)
{
	char	*token;
	int		i;

	i = *start;
	while (i < end && s[i] != ' ' && s[i] != '\t')
		i++;
	if (s[*start] == '\'' || s[*start] == '\"')
		i -= 2;
	token = ft_calloc(i - *start + 1, sizeof(char));
	if (!token)
		return (NULL);
	i = 0;
	while (*start < end && s[*start] != ' ' && s[*start] != '\t')
	{
		token[i] = s[*start];
		i++;
		*start += 1;
	}
	return (token);
}

t_token	*ft_new_token(char *s, int *start, int end, t_token *tokens)
{
	t_token	*token;
	t_token	*tmp;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (ft_free_tokens(tokens));
	token->s = ft_extract_token(s, start, end);
	if (!token->s)
	{
		free(token);
		return (ft_free_tokens(tokens));
	}
	token->is_string = ft_get_type(token->s);
	token->next = NULL;
	tmp = tokens;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		tokens = token;
	else
		tmp->next = token;
	return (tokens);
}

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
t_token	*get_tokens(char *s, int start, int end)
{
	t_token	*tokens;

	while (start < end)
	{
		while (start < end && (s[start] == ' ' || s[start] == '\t'))
			start++;
		tokens = ft_new_token(s, &start, end, tokens);
	}
}

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
	if (*wcard == '*')
		return (match_wildcard(wcard, s));
	else if (*s)
		return (-1);
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
