/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:09:36 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/17 11:16:17 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft/libft.h"

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

/**
 * @brief Given a string without () && ||, execute the command
 * @note this may include pipes, redirs, etc, but is self contained
 * @param s 
 * @param start 
 * @param end 
 * @return int 
 */
int		eval_str(char *s, int start, int end);
