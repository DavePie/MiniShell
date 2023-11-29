/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:56:10 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/29 13:58:57 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

int	unset(t_data *d, char *av[])
{
	int			i;
	t_export	*tmp;

	i = 1;
	while (av[i])
	{
		tmp = export_find(*d->exports, av[i]);
		if (tmp)
			export_remove(d->exports, tmp);
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
		i++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		exit_shell(1, "unable to allocate space");
	i = 0;
	tmp = *list;
	while (tmp)
	{
		tab[i++] = ft_strjoin(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	is_builtin(char *cmd)
{
	static char	*builtin[7] = {"pwd", "cd", "env", "export",
		"unset", NULL};
	int			i;

	i = 0;
	while (builtin[i])
	{
		if (!ft_strcmp(builtin[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

int	cmd_exe(char *av[], t_data *d)
{
	char		*path;
	char		**env_tab;
	static char	*builtin[7] = {"echo", "pwd", "cd", "env", "export",
		"unset", NULL};
	static int	(*builtin_func[7])(t_data *, char **) = {&echo, &pwd, &cd,
		&env, &export, &unset, NULL};
	int			i;

	i = -1;
	while (builtin[++i])
	{
		if (!ft_strcmp(builtin[i], av[0]))
			return (builtin_func[i](d, av));
	}
	path = get_command_path(av[0]);
	env_tab = export_to_tab(d->exports);
	if (execve(path, av, env_tab) == -1)
	{
	}
	ft_perror(av[0]);
	ft_free_str_tab(env_tab);
	path = ft_free(path);
	exit(1);
}
