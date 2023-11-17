/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:50:45 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/16 12:32:41 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_replace(char *s1, char *s2, int pos, int len)
{
	char	*new_s;

	new_s = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1 - len, sizeof(char));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s1, pos + 1);
	ft_strlcat(new_s, s2, pos + ft_strlen(s2) + 1);
	ft_strlcat(new_s, s1 + pos + len, ft_strlen(s1) + ft_strlen(s2) + 1 - len);
	free(s1);
	free(s2);
	return (new_s);
}
