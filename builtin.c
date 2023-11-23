/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:56:10 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/23 11:56:59 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
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

int	cd(char *path, char **envp)
{
	char	*home;

	if (!path)
	{
		while (envp && *envp)
		{
			if (!ft_strncmp(*envp, "HOME=", 5))
				path = *envp + 5;
			envp++;
		}
		if (!path)
			return (-2);
		home = ft_strdup(path);
		path[0] = '/';
		path[strlen(path) - 2] = 0;
		return (chdir(home));
	}
	return (chdir(path));
}


