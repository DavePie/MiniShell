/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:38:29 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/01 10:05:59 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "structs.h"

int		echo(t_data *d, char*av[]);
int		pwd(t_data *d, char *av[]);
int		cd(t_data *d, char *av[]);
int		env(t_data *d, char *av[]);
int		is_valid_key(char *key);
int		export(t_data *d, char *av[]);
int		unset(t_data *d, char *av[]);
char	**export_to_tab(t_export **list);
int		cmd_exe(char *av[], t_data *d);
int		is_builtin(char *cmd);
int		write_export_error(char *name, char *input);
void	change_pwd(t_data *d);

#endif