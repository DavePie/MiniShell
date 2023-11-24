/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:56:10 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/24 14:04:42 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(int ac, char*av[])
{
	int	nl;
	int	i;

	if (ac == 1)
	{
		printf("\n");
		return (0);
	}
	nl = ft_strcmp("-n", av[1]);
	i = 1 + nl;
	while (i < ac)
		printf("%s", av[i++]);
	if (nl)
		printf("\n");
	return (0);
}

int	pwd(void)
{
	char	*pwd;
	int		printf_return;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	printf_return = printf("%s\n", pwd);
	free(pwd);
	return (printf_return);
}

int	cd(char *path, t_export **export)
{
	char	*home;

	home = NULL;
	if (!path)
	{
		home = export_find(export, "HOME");
		if (!home)
			return (-2);
		return (chdir(home));
	}
	return (chdir(path));
}

int	env(t_export *list)
{
	while (list)
	{
		if (!list->is_export)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (0);
}

int	export(t_export *list, char *av[])
{
	int	i;

	i = 1;
	while (!av && list)
	{
		printf("declare -x %s=\"%s\"\n", list->key, list->value);
		list = list->next;
	}
	while (av[i])
	{
		export_add(av[i], list, 1);
		i++;
	}
	return (0);
}

int	unset(t_export **list, char *av[])
{
	int			i;
	t_export	*tmp;

	i = 1;
	while (av[i])
	{
		tmp = export_find(list, av[i]);
		export_remove(av[i], list);
		i++;
	}
	return (0);
}
