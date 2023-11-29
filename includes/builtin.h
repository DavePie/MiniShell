/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:38:29 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/29 15:46:30 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "structs.h"

int		echo(t_data *d, char*av[]);
int		pwd(t_data *d, char *av[]);
int		cd(t_data *d, char *av[]);
int		env(t_data *d, char *av[]);
int		export(t_data *d, char *av[]);
int		unset(t_data *d, char *av[]);
char	**export_to_tab(t_export **list);
int		cmd_exe(char *av[], t_data *d);
int		is_builtin(char *cmd);

#endif