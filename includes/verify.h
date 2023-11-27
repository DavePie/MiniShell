/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:07:21 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/23 16:19:11 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERIFY_H
# define VERIFY_H

/**
 * @brief Verifies that input is valid
 * 
 * @param s the input
 * @return int (if it is valid)
 */
int		verify_input(char *s);

/**
 * @brief Verifies that paranthesis are valid
 * 
 * @param s 
 * @return int 
 */
int		verify_paranthesis(char *s);

/**
 * Allowed cases: && (, ) ||, )))
 * Illegal cases: ( ), ) (, && ||, | >>, || ||, ( && etc
 */

/**
 * @brief Verifies that special characters aren't adjacent
 * 
 * @param s the string
 * @return char * (the second adjacent character) 
 */
char	*verify_special_characters(char *s);

/**
 * @brief Verify no special chars around edges
 * @note && | || > >> < <<, paran fine
 * @param s the string
 * @return char * (returns the invalid special chars)
 */
char	*verify_edges(char *s);

/**
 * @brief Verify that strings close
 * 
 * @param s the input
 * @return int (if valid)
 */
int		verify_str(char *s);

/**
 * @brief Verify that outside parenthesis there is only logic
 * @note Valid: a && (b || c), Invalid: (a) (b)
 * @param s the input
 * @return char (if there is an unexpected char, return it)
 */
char	verify_paren_logic(char *s);

#endif