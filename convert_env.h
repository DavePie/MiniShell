/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:04:00 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/20 11:04:45 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_ENV_H
# define CONVERT_ENV_H
# include "tokens.h"

t_token	**ft_convert_envs(t_token **tokens, char **envp);

#endif