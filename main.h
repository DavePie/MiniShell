/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:07:21 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/10 13:06:36 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

/**
 * @brief Checks that paranthesis work, no stray logic operators (&& || ())
 * @note (echo a &&)) &&
 * @note ()
 * @note &&((echo b)
 * @param s the user input
 * @return int if it is valid
 */
int	verify_logic(char *s);

/**
 * @brief Checks that there are no stray pipe/redir operators (| > >> < <<)
 * 
 * @param s 
 * @return int 
 */
int	verify_pipes_redir(char *s);

/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
int handle_special_characters(char *s);


/**
 * @brief Checks that the given token always has a command after it
 * @note token must not be inside a string
 * @param s 
 * @param token 
 * @return int 
 */
int	has_command_around(char *s, char token);

#endif