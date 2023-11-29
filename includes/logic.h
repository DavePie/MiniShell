/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:10:04 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/29 17:27:38 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGIC_H
# define LOGIC_H
# include "minishell.h"

/**
 * @brief Given a string, return if the given index is a logical parameter
 * @note logical parameters can't be in strings. They are ( ) && ||
 * @param str the string
 * @param i the index
 * @return int (if a logical parameter)
 */
int	is_logic(char *str, int i);

/**
 * @brief Get the index of the next operator
 * 
 * @param str input command
 * @param op operator (&&, ||)
 * @param start starting index
 * @return int 
 */
int	get_next_command(char *str, char *op, int start);

/**
 * @brief Given a string and a starting point, return the next av
 * 
 * @param str 
 * @param start 
 * @return int 
 */
int	run_command_at(t_data *d, int start);

/**
 * @brief Handles the logic layer runs the commands as needed
 * 
 * @param str 
 * @return int 
 */
int	run_all_commands(t_data *d);
#endif