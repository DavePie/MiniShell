/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:16:16 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/28 13:20:34 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token
{
	int				is_string;
	char			*token;
	struct s_token	*next;
	int				adj_prev;
}	t_token;

typedef struct s_export
{
	char			*key;
	char			*value;
	int				is_export;
	struct s_export	*prev;
	struct s_export	*next;
}	t_export;

typedef struct s_data
{
	char		*input;
	char		*command;
	t_token		**tokens;
	t_export	**exports;
}	t_data;

#endif