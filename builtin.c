/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:56:10 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/13 13:33:39 by dvandenb         ###   ########.fr       */
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

