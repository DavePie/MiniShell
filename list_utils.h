/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:24:13 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/17 10:53:28 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_UTILS_H
# define LIST_UTILS_H
# include "tokens.h"

t_token	*t_new(char *token, int isstr);

int		t_size(t_token *lst);

t_token	*t_get_last(t_token *start);

void	t_del(t_token **begin_list, t_token *prev);

t_token	*t_add_back(t_token **lst, t_token *new_t);

t_token	*t_insert(t_token *dest, t_token *src);

t_token	*t_replace(t_token **first,
			t_token *prev, t_token *arg, t_token *to_add);

#endif