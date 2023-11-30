/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_input2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:31:25 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/30 15:43:00 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "logic.h"
#include "utils_shell.h"
#include "libft.h"
#include "minishell.h"
#include "verify.h"

char	*verify_edges(char *s)
{
	const char	*end[8] = {"&&", "||", "|", "<<", ">>", "<", ">", 0};
	const char	*start[4] = {"&&", "||", "|", 0};
	int			i;
	int			j;
	int			k;

	i = 0;
	k = ft_strlen(s) - 1;
	if (k < 0)
		return (0);
	while (s[i] && is_s(s[i]))
		i++;
	while (k > 0 && s[k] && is_s(s[k]))
		k--;
	if (k > 0 && (s[k] == '&' || (s[k] == '|' && s[k - 1] == '|')))
		k--;
	j = -1;
	while (end[++j])
		if (str_at(s, k, (char *)end[j]))
			return ((char *)end[j]);
	j = -1;
	while (start[++j])
		if (str_at(s, i, (char *)start[j]))
			return ((char *)start[j]);
	return (0);
}

char	verify_paren_logic(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		if (!instr(s, i) && s[i] == '(' && i > 0)
		{
			j = i - 1;
			while (is_s(s[j]) && j > 0 && s[j] != '(')
				j--;
			if (j > 0 && !is_logic(s, j))
				return (s[j]);
		}
		if (!instr(s, i) && s[i] == ')')
		{
			j = i + 1;
			while (s[j] && is_s(s[j]))
				j++;
			if (s[j] && !is_logic(s, j) && s[j] != ')')
				return (s[j]);
		}
		i++;
	}
	return (0);
}

int	verify_input(char *s)
{
	if (verify_paren_logic(s))
		return (e_token_write("&& or ||", "missing"));
	if (verify_edges(s))
		return (e_token_write(verify_edges(s), "unexpected"));
	if (verify_special_characters(s, 0, 0))
		return (e_token_write(verify_special_characters(s, 0, 0), "unexpected"));
	return (verify_paranthesis(s) && verify_str(s));
}
