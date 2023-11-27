/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:05:33 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/23 15:24:49 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H
# include "minishell.h"

t_token	**convert_wildcards(t_token **list);

t_token	*replace_wildcard(t_token **first, t_token *prev, t_token *cur);

int		ft_is_star(t_token *token);
#endif