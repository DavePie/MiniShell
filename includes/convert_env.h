/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:04:00 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/23 16:18:33 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_ENV_H
# define CONVERT_ENV_H
# include "minishell.h"

t_token	**ft_convert_envs(t_token **tokens);

int		ft_is_env(char *s);

char	*ft_get_env_var(char *s);

t_token	*ft_split_token(t_token **tokens, t_token *cur,
			t_token *prev, int adj_prev);

char	*ft_insert_env(char **token, char *env);

char	*ft_get_env(char *s);

#endif