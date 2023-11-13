/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:48:42 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/13 11:59:21 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_SHELL_H
# define UTILS_SHELL_H

/**
 * @brief Given an error message, write it in the correct format
 * @note minishell: <error-message>
 * @param s 
 * @return int 
 */
int	ewrite(char *s);

#endif