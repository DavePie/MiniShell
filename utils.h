/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:08:31 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/10 12:22:02 by dvandenb         ###   ########.fr       */
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
int		instr(char *s, int i);




#endif