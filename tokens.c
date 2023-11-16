/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:09:36 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/16 09:16:49 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft/libft.h"

char	*ft_get_env_var(char *s, char *end)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	while (s + i < end && s[i] != ' ' && s[i]
		!= '\t' && s[i] != '$')
		i++;
	if (s[i] != '$')
		return (NULL);
	j = 0;
	while (s + i + j < end && s[i + j] != ' ' && s[i + j] != '\t')
		j++;
	env = ft_calloc(j + 1, sizeof(char));
	if (!env)
		return (NULL);
	j = 0;
	while (s + i + j < end && s[i + j] != ' ' && s[i + j] != '\t')
	{
		env[j] = s[i + j];
		j++;
	}
	return (env);
}

char	*ft_get_env(char **envp, char *s, char *end)
{
	char	*env;

	env = ft_get_env_var(s, end);
	if (!env)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(env, *envp, ft_strlen(env)) == 0)
		{
			free(env);
			env = ft_strndup (*envp + ft_strlen(env) + 2,
					ft_strlen(*envp) - ft_strlen(env) - 3);
			if (!env)
				return (NULL);
			return (env);
		}
		envp++;
	}
	free(env);
	return (NULL);
}

char	*ft_modify_s_if_env(char **s, char *end, char **envp)
{
	char	*env;
	int		i;
	char	*new_s;

	env = ft_get_env(envp, *s, end);
	if (!env)
		return (NULL);
	i = 0;
	while (*s + i < end && (*s)[i] != ' ' && (*s)[i] != '\t' && (*s)[i] != '$')
		i++;
	new_s = ft_calloc(i + ft_strlen(env) + 1, sizeof(char));
	if (!new_s)
		return (NULL);
	i = 0;
	while (*s < end && *s != ' ' && *s != '\t' && *s != '$')
	{
		new_s[i] = **s;
		(*s)++;
		i++;
	}
	ft_strcat(new_s, env);
	while (*s < end && *s != ' ' && *s != '\t')
		(*s)++;
	free (env);
}

int	ft_is_wildcard(char *s, char *end)
{
	while (*s && s < end && *s != ' ' && *s != '\t')
	{
		if (*s == '*')
			return (1);
		s++;
	}
	return (0);
}

int	ft_add_wildcard(char **s, char *end, t_token *tokens)
{
	int		i;
	char	*wcard;
	char	**elems;

	i = 0;
	while (*s + i < end && (*s)[i] != ' ' && (*s)[i] != '\t')
		i++;
	wcard = ft_strndup(*s, i);
	*s += i;
	elems = get_wildcard(wcard, "./");
	i = 0;
	while (elems[i])
	{
		tokens = ft_new_token(&elems[i], elems[i] + ft_strlen(elems[i]),
				tokens);
		i++;
	}
	ft_free_str_tab(elems);
	free(wcard);
}

int	ft_is_env(char *s, char *end)
{
	while (*s && s < end && *s != ' ' && *s != '\t')
	{
		if (*s == '$' && s + 1 < end && *s != ' ' && *s != '\t')
			return (1);
		s++;
	}
	return (0);
}

int	ft_add_env(char **s, char *end, t_token *tokens, char **envp)
{
	int		i;
	char	*new_s;

	new_s = ft_get_env(envp, *s, *s + i);
	if (!new_s)
		return (-1);
	while (new_s)
	{
		if (ft_is_wildcard)
			ft_add_wildcard(&new_s, new_s + ft_strlen(new_s), tokens);
		else
			tokens = ft_new_token(&(new_s[i]), new_s
					+ ft_strlen(new_s), tokens);
		while (new_s[i] && new_s[i] != ' ' && new_s[i] != '\t')
			i++;
		while (new_s[i] && new_s[i] == ' ' && new_s[i] == '\t')
			i++;
	}
	free(new_s);
	return (0);
}

t_token	*ft_free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->token);
		free(tokens);
		tokens = tmp;
	}
	return (NULL);
}

char	*ft_extract_token(char **s, char *end)
{
	char	*token;
	int		i;

	i = 0;
	while (*s + i < end && (*s)[i] != ' ' && (*s)[i] != '\t')
		i++;
	if (**s == '\'' || **s == '\"')
		i -= 2;
	token = ft_calloc(i - 1, sizeof(char));
	if (!token)
		return (NULL);
	i = 0;
	while (*s + i < end && (*s)[i] != ' ' && (*s)[i] != '\t')
	{
		token[i] = (*s)[i];
		i++;
	}
	*s += i;
	return (token);
}

t_token	*ft_new_token(char **s, char *end, t_token *tokens)
{
	t_token	*token;
	t_token	*tmp;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (ft_free_tokens(tokens));
	token->token = ft_extract_token(s, end, envp);
	if (!token->token)
	{
		free(token);
		return (ft_free_tokens(tokens));
	}
	token->is_string = ft_get_type(token->token);
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
 * @brief Given a single space/tab delimited string, return an linked list of tokens
 * @param s string, with bounds determined by:
 * @param start index
 * @param end index
 * @return t_token* 
 */
t_token	*get_tokens(char *s, char *end, char **envp)
{
	t_token	*tokens;

	while (s < end)
	{
		while (s < end && (*s == ' ' || *s == '\t'))
			s++;
		tokens = ft_new_token(&s, end, tokens, envp);
	}
	return (tokens);
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
