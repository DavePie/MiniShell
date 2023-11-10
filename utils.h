/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:08:31 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/10 13:50:39 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/**
 * @brief Returns if the selected index is within quotes
 * emphasis on the outermost quotes
 * 
 * @param s the string to search
 * @param i the index
 * @return int 1 if single quote, 2 if double quote
 */
int	instr(char *s, int i);

/**
 * @brief Given a string, return its length
 * 
 * @param s the string
 * @return int (its length)
 */
int	ft_strlen(const char *s);

/**
 * @brief Given an error message, write it in the correct format
 * @note minishell: <error-message>
 * @param s 
 * @return int 
 */
int	ewrite(char *s);

#endif