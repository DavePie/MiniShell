/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:56:10 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/27 15:55:11 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_export **list, char*av[])
{
	(void)list;
	(void)av;
	// int	nl;
	// int	i;

	// if (ac == 1)
	// {
	// 	printf("\n");
	// 	return (0);
	// }
	// nl = ft_strcmp("-n", av[1]);
	// i = 1 + nl;
	// while (i < ac)
	// 	printf("%s", av[i++]);
	// if (nl)
	// 	printf("\n");
	return (0);
}

int	pwd(t_export **list, char *av[])
{
	char	*pwd;
	int		printf_return;

	(void)list;
	(void)av;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	printf_return = printf("%s\n", pwd);
	free(pwd);
	return (printf_return);
}

int	cd(t_export **list, char *av[])
{
	t_export	*home;

	home = NULL;
	if (!av[1])
	{
		home = export_find(*list, "HOME");
		if (!home)
			return (-2);
		return (chdir(home->value));
	}
	return (chdir(av[1]));
}

int	env(t_export **list, char *av[])
{
	(void)av;
	while ((*list))
	{
		if (!(*list)->is_export)
			printf("%s=%s\n", (*list)->key, (*list)->value);
		(*list) = (*list)->next;
	}
	return (0);
}

int	export(t_export **list, char *av[])
{
	int	i;

	i = 1;
	while (!av && list)
	{
		printf("declare -x %s=\"%s\"\n", (*list)->key, (*list)->value);
		(*list) = (*list)->next;
	}
	while (av[i])
	{
		export_add(list, av[i], 1);
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
		tmp = export_find(*list, av[i]);
		if (tmp)
			export_remove(list, tmp);
		i++;
	}
	return (0);
}

char	**export_to_tab(t_export **list)
{
	char		**tab;
	int			i;
	t_export	*tmp;

	i = 0;
	tmp = *list;
	while (tmp)
	{
		if (!tmp->is_export)
			i++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		ft_error("Malloc error");
	i = 0;
	tmp = *list;
	while (tmp)
	{
		if (!tmp->is_export)
			tab[i++] = ft_strjoin(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	cmd_exe(char *av[], t_export **envp)
{
	char		*path;
	char		**env_tab;
	static char	*builtin[7] = {"echo", "pwd", "cd", "env", "export",
		"unset", NULL};
	static int	(*builtin_func[7])(t_export **, char **) = {&echo, &pwd, &cd,
		&env, &export, &unset, NULL};
	int			i;

	i = 0;
	while (builtin[i])
	{
		if (!ft_strcmp(builtin[i], av[0]))
			return (builtin_func[i](envp, av));
		i++;
	}
	path = get_command_path(av[0]);
	env_tab = export_to_tab(envp);
	if (execve(path, av, env_tab) == -1)
		ft_error("Execve error");
	path = ft_free(path);
	exit(1);
}
