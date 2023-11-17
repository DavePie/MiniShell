/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:16:39 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/17 14:50:35 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft/libft.h"

int	ft_is_wildcard(char *s)
{
	while (*s && *s != ' ' && *s != '\t')
	{
		if (*s == '*')
			return (1);
		s++;
	}
	return (0);
}

char	*wcard_len(char *s)
{
	int	i;
	int	wc_len;

	i = 0;
	wc_len = 0;
	while (s[i])
	{
		if (s[i] == '*' && s[i + 1] != '*')
			wc_len++;
		else if (s[i] != '*')
			wc_len++;
		i++;
	}
}

char	*clean_wcard(char *s)
{
	char	*wcard;
	int		i;
	int		j;

	i = 0;
	j = 0;
	wcard = ft_calloc(wcard_len(s), sizeof(char));
	if (!wcard)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '*' && s[i + 1] != '*')
		{
			wcard[j] = '*';
			j++;
		}
		else if (s[i] != '*')
		{
			wcard[j] = s[i];
			j++;
		}
		i++;
	}
	return (wcard);
}

char	**get_wildcard(char *s, char *dir)
{
	DIR				*directory;
	struct dirent	*elem;
	char			**elems;
	int				n;
	char			*wcard;

	wcard = clean_wcard(s);
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
	elems = get_wc_elems(elems, n, dir, wcard);
	free(wcard);
	return (elems);
}

char	**get_wc_elems(char **elems, int n, char *dir, char *wcard)
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

int	strstarcmp(char **wcard, char **s)
{
	int	i;

	while (**s && **wcard)
	{
		if (**s != **wcard)
			*s += 1;
		else if (**s == **wcard)
		{
			i = 0;
			while ((*s)[i] && (*wcard)[i] && (*wcard)[i]
				!= '*' && (*s)[i] == (*wcard)[i])
				i++;
			if ((*wcard)[i] == '*' || !(*wcard)[i])
			{
				*wcard += i;
				s += i;
				return (1);
			}
			*s += 1;
		}
	}
}

int	match_wildcard(char *wcard, char *s)
{
	while (*s && *wcard)
	{
		if (*wcard == '*' && !*(wcard + 1))
			return (1);
		else if (*wcard == '*')
		{
			wcard++;
			while (*s && *s != *wcard)
				s++;
		}
		else if (!strstarcmp(&wcard, &s))
			return (0);
	}
	return (1);
}

void	ft_split_token(t_token **tokens, t_token *cur, t_token *prev, char **wildcard)
{
	t_token	**split;
	t_token	*tmp;
	int		i;

	i = 0;
	while (wildcard[i])
	{
		tmp = t_new(wildcard[i], 0);
		t_add_back(split, tmp);
		tmp->token = ft_strdup(wildcard[i]);
	}
	t_replace(tokens, prev, cur, *split);
}

t_token	**ft_convert_wildcards(t_token **tokens)
{
	t_token	*cur;
	t_token	*prev;
	char	**wildcards;

	cur = *tokens;
	prev = NULL;
	while (cur)
	{
		if (!cur->is_string && ft_is_wildcard(cur->token))
		{
			wildcards = get_wildcard(cur->token, "./");
			ft_insert_wildcards(tokens, cur, prev, wildcards);
			ft_free_str_tab(wildcards);
		}
		prev = cur;
		cur = cur->next;
	}
	return (tokens);
}
