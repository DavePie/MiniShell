/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:16:15 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/23 16:19:58 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_utils.h"
#include "utils.h"
#include "minishell.h"
#include "libft.h"
#include "convert_env.h"

int	remove_env_token(t_token **tokens, char *env, t_token **cur, t_token **prev)
{
	if (!(env || (*cur)->is_string == DOUBLE))
	{
		t_del(tokens, *prev);
		*cur = *tokens;
		if (*prev)
			*cur = (*prev)->next;
		return (1);
	}
	return (0);
}

t_token	**ft_convert_envs(t_token **tokens)
{
	t_token	*cur;
	t_token	*prev;
	char	*env;

	cur = *tokens;
	prev = NULL;
	while (cur)
	{
		if (cur->is_string != SINGLE && ft_is_env(cur->token))
		{
			env = ft_get_env(cur->token);
			if (env || cur->is_string == DOUBLE)
				cur->token = ft_insert_env(&cur->token, env);
			if (cur->is_string == 0 && (env || cur->is_string == DOUBLE))
				cur = ft_split_token(tokens, cur, prev,
						cur->adj_prev * !is_s(*cur->token));
			remove_env_token(tokens, env, &cur, &prev);
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
	return (tokens);
}
