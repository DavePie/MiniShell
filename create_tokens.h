/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:06:36 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/23 14:04:37 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_TOKENS_H
# define CREATE_TOKENS_H
# include "minishell.h"

t_token	**split_args(char *input);
void	merge_tokens(t_token *cur, int ignore_wild);
#endif