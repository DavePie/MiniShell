/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:10:04 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/10 15:21:37 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGIC_H
# define LOGIC_H

/**
 * @brief Get the index of the next operator
 * 
 * @param str input command
 * @param op operator (&&, ||)
 * @param start starting index
 * @return int 
 */
int	get_next_command(char *str, char* op, int start);

/**
 * @brief Handles the logic layer runs the commands as needed
 * 
 * @param str 
 * @return int 
 */
int	run_all_commands(char *str);
#endif