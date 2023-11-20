/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:42:02 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/20 11:40:34 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "list_utils.h"
#include "utils.h"
#include "minishell.h"
#include "libft.h"

int	ft_is_env(char *s)
{
	while (*s)
	{
		if (*s == '$' && *(s + 1) != '\0' && !is_s(*(s + 1)))
			return (1);
		s++;
	}
	return (0);
}

char	*ft_get_env_var(char *s)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	while (s[i] && !is_s(s[i]) && s[i] != '$')
		i++;
	if (s[i] != '$')
		return (NULL);
	j = 0;
	while (s[i + j] && !is_s(s[i + j]))
		j++;
	env = ft_calloc(j + 1, sizeof(char));
	if (!env)
		return (NULL);
	j = 0;
	while (s[i + j] && !is_s(s[i]))
	{
		env[j] = s[i + j];
		j++;
	}
	return (env);
}

char	*ft_get_env(char **envp, char *s)
{
	char	*env;

	env = ft_get_env_var(s);
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

char	*ft_insert_env(char *s, char *env)
{
	return (ft_str_replace(s, env, ft_strchr(s, '$') - s, ft_strlen(env) + 1));
}

void	ft_split_token(t_token **tokens, t_token *cur, t_token *prev, int adj_prev)
{
	t_token	**split;
	t_token	*tmp;
	char	**strs;
	int		i;

	i = 0;
	split = NULL;
	if (is_s(*cur->token))
		adj_prev = 0;
	strs = ft_split((const char *)cur->token, ' ');
	while (strs[i])
	{
		ft_strtrim(strs[i], "\t");
		i++;
	}
	i = 0;
	while (strs[i])
	{
		tmp = t_new(strs[i], 0);
		t_add_back(split, tmp);
		tmp->token = ft_strdup(strs[i]);
	}
	(*split)->adj_prev = adj_prev;
	t_replace(tokens, prev, cur, *split);
	ft_free_str_tab(strs);
}

t_token	**ft_convert_envs(t_token **tokens, char **envp)
{
	t_token	*cur;
	t_token	*prev;
	char	*env;

	cur = *tokens;
	prev = NULL;
	while (cur)
	{
		printf("token: %s\n", cur->token);
		if (cur->is_string != SINGLE && ft_is_env(cur->token))
		{
			env = ft_get_env(envp, cur->token);
			cur->token = ft_insert_env(cur->token, env);
			if (cur->is_string == 0)
				ft_split_token(tokens, cur, prev, cur->adj_prev);
		}
		prev = cur;
		cur = cur->next;
	}
	return (tokens);
}
