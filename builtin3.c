/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:56:10 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/30 16:18:26 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

int	is_valid_key(char *key)
{
	int		i;
	char	*k_v[2];
	int		ret;

	ret = 1;
	ft_split_export(key, k_v);
	if (!k_v[0] || !*k_v[0] || !(ft_isalpha(*k_v[0]) || *k_v[0] == '_'))
		ret = 0;
	i = 0;
	while (ret && k_v[0][i])
	{
		if (!ft_isalnum(k_v[0][i]) && k_v[0][i] != '_')
			ret = 0;
		i++;
	}
	free(k_v[0]);
	if (k_v[1])
		free(k_v[1]);
	return (ret);
}
