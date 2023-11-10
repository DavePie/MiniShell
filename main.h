/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:07:21 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/10 17:10:54 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

/**
 * @brief Verifies that input is valid
 * 
 * @param s the input
 * @return int (if it is valid)
 */
int	verify_input(char *s);

/**
 * @brief Verifies that paranthesis are valid
 * 
 * @param s 
 * @return int 
 */
int	verify_paranthesis(char *s);

/**
 * Allowed cases: && (, ) ||, )))
 * Illegal cases: ( ), ) (, && ||, | >>, || ||, ( && etc
 */

/**
 * @brief Verifies that special characters aren't adjacent
 * 
 * @param s 
 * @return int 
 */
int	verify_special_characters(char *s);

/**
 * @brief Checks that the given token always has a command after it
 * @note token must not be inside a string
 * @param s 
 * @param token 
 * @return int 
 */
int	has_command_around(char *s, char token);

#endif