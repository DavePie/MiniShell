/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:56:10 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/28 17:43:55 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

int	echo(t_data *d, char*av[])
{
	int	i;

	i = 1 + (av[1] && !ft_strcmp("-n", av[1]));
	(void)d;
	(void)av;
	while (av[i] && av[i + 1])
	{
		printf("%s ", av[i]);
		i++;
	}
	if (av[i])
		printf("%s", av[i]);
	if (!av[1] || ft_strcmp("-n", av[1]))
		printf("\n");
	return (0);
}

int	pwd(t_data *d, char *av[])
{
	char	*pwd;
	int		printf_return;

	(void)d;
	(void)av;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	printf_return = printf("%s\n", pwd);
	free(pwd);
	return (printf_return);
}

int	cd(t_data *d, char *av[])
{
	t_export	*home;

	home = NULL;
	if (!av[1])
	{
		home = export_find(*d->exports, "HOME");
		if (!home)
			return (-2);
		return (chdir(home->value));
	}
	return (chdir(av[1]));
}

int	env(t_data *d, char *av[])
{
	t_export	*list;

	list = *d->exports;
	(void)av;
	while (list)
	{
		if (!list->is_export)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (0);
}

int	export(t_data *d, char *av[])
{
	int			i;
	t_export	*list;

	list = *d->exports;
	i = 1;
	while (!av[1] && list)
	{
		printf("declare -x %s=\"%s\"\n", list->key, list->value);
		list = list->next;
	}
	while (av[i])
	{
		export_add(d->exports, av[i], 1);
		i++;
	}
	return (0);
}
