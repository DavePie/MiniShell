/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:42:02 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/29 17:39:21 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] != '$')
		return (NULL);
	i++;
	j = 0;
	while (s[i + j] && !is_s(s[i + j]) && s[i + j] != '$')
		j++;
	env = ft_calloc(j + 1, sizeof(char));
	if (!env)
		exit_shell(1, "unable to allocate space");
	j = 0;
	while (s[i + j] && !is_s(s[i + j]) && s[i + j] != '$')
	{
		env[j] = s[i + j];
		j++;
	}
	return (env);
}

char	*ft_get_env(char *s, t_data *d)
{
	char	*env;
	char	*env_var;

	env_var = ft_get_env_var(s);
	if (!env_var)
		return (NULL);
	env = 0;
	if (export_find(*d->exports, env_var))
		env = export_find(*d->exports, env_var)->value;
	free(env_var);
	if (!env)
		return ("");
	return (env);
}

char	*ft_insert_env(char **token, char *env)
{
	char	*env_var;
	char	*modified_s;
	int		i;
	char	*s;

	s = *token;
	env_var = ft_get_env_var(s);
	modified_s = ft_calloc(ft_strlen(s) - ft_strlen(env_var)
			+ ft_strlen(env) + 1, sizeof(char));
	if (!modified_s)
		exit_shell(1, "unable to allocate space");
	i = 0;
	while (s[i] && s[i] != '$')
	{
		modified_s[i] = s[i];
		i++;
	}
	i += ft_strlen(env_var) + 1;
	ft_strlcat(modified_s, env, i + ft_strlen(env) + 1);
	ft_strlcat(modified_s, s + i, i + ft_strlen(env) + ft_strlen(s) - i + 1);
	if (*token)
		free(*token);
	*token = 0;
	free(env_var);
	return (modified_s);
}

t_token	*ft_split_token(t_token **tokens, t_token *cur,
	t_token *prev, int adj_prev)
{
	t_token	*split;
	char	**strs;
	int		i;

	split = NULL;
	if (!(ft_strchr(cur->token, ' ') || ft_strchr(cur->token, '\t')))
		return (cur);
	strs = ft_split2((const char *)cur->token, " \t");
	i = 0;
	while (strs[i])
	{
		if (!t_add_back(&split, t_new(ft_strdup(strs[i]), 0)))
			exit_shell(1, "unable to allocate space");
		i++;
	}
	split->adj_prev = adj_prev;
	cur = t_replace(tokens, prev, cur, split);
	ft_free_str_tab(strs);
	return (cur);
}
