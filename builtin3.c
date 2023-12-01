/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:56:10 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/01 10:05:43 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "utils_shell.h"

int	is_valid_key(char *key)
{
	int		i;
	char	*k_v[2];
	int		ret;

	ret = 1;
	ft_split_export(key, k_v);
	if (!k_v[0] || !*k_v[0] || (ft_isdigit(*k_v[0])))
		ret = 0;
	i = 0;
	while (ret && k_v[0][i])
	{
		if (ft_strchr("=&|()\"'", k_v[0][i]))
			ret = 0;
		i++;
	}
	free(k_v[0]);
	if (k_v[1])
		free(k_v[1]);
	return (ret);
}

int	write_export_error(char *name, char *input)
{
	fdwrite(2, "minishell: ");
	fdwrite(2, name);
	fdwrite(2, ": `");
	fdwrite(2, input);
	fdwrite(2, "': not a valid identifier\n");
	return (1);
}

void	change_pwd(t_data *d)
{
	char	*cwd;
	char	*pwd;

	cwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	export_modify(d->exports, pwd);
}
