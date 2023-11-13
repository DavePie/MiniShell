/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:08:31 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/13 11:49:26 by dvandenb         ###   ########.fr       */
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
 * @brief Compare two strings
 * 
 * @param s 
 * @param r 
 * @return int 
 */
int	ft_strcmp(char *s, char *r);

/**
 * @brief Given two strings, state if the second string is in the first
 * at the starting index given
 * 
 * @param str first string (stack)
 * @param index starting index
 * @param input second string (needle)
 * @return int (if found)
 */
int	str_at(char *str, int index, char *input);

/**
 * @brief Returns if the given character is a whitespace character
 * @note currently space and tab
 * @param c the char
 * @return int (if whitespace)
 */
int	is_s(char c);
#endif