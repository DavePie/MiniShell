/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:07:11 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/28 13:45:06 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert_env.h"
#include "minishell.h"
#include "wildcards.h"
#include "create_tokens.h"
#include "libft.h"
#include "commands.h"
#include "list_utils.h"
#include "pipe.h"
#include "utils_shell.h"

int	open_fd(char *name, int prev, int type)
{
	int	fd;
	int	tags;
	int	mode;

	if (prev > 0)
		close(prev);
	tags = O_RDONLY;
	mode = 0;
	if (type == OUT)
	{
		tags = O_WRONLY | O_CREAT | O_TRUNC;
		mode = 0644;
	}
	else if (type == OUT_A)
	{
		tags = O_WRONLY | O_CREAT | O_APPEND;
		mode = 0644;
	}
	if (type != IN_D)
		fd = open(name, tags, mode);
	else
		fd = exec_redir(name);
	if (fd == -1)
		ft_perror(name);
	return (fd);
}

void	print_tokens(t_token *cur)
{
	while (cur)
	{
		printf("[%s](s:%d)(ad:%d), ",
			cur->token, cur->is_string, cur->adj_prev);
		cur = cur->next;
	}
	printf("\n");
}

int	exec_next_command(t_data *d, t_token **cur, t_com *cmd, int l)
{
	t_token	*first;

	first = *cur;
	while (*cur && cmd->i_fd != -1 && cmd->o_fd != -1)
	{
		if (type_t(*cur) == OUT || type_t(*cur) == OUT_A)
			cmd->o_fd = open_fd((*cur)->next->token, cmd->o_fd, type_t(*cur));
		else if (type_t(*cur) == IN || type_t(*cur) == IN_D)
			cmd->i_fd = open_fd((*cur)->next->token, cmd->i_fd, type_t(*cur));
		else if (type_t(*cur) == PIPE)
		{
			if (cmd->o_fd == OUTPUT_STD)
				cmd->o_fd = OUTPUT_PIPE;
			(*cur) = (*cur)->next;
			cmd->is_pipe = 1;
			break ;
		}
		if (type_t(*cur))
			(*cur) = (*cur)->next;
		else
			l++;
		(*cur) = (*cur)->next;
	}
	set_cmd_args(first, l, cmd);
	return (ft_fork_and_exec(d, cmd));
}

int	exec_commands(t_data *d, char **envp)
{
	t_token	*cur;
	t_com	cur_c;
	int		prev;

	cur = *d->tokens;
	prev = NO_INPUT;
	while (cur)
	{
		cur_c = (t_com){.env = envp, .i_fd = prev, .o_fd = OUTPUT_STD};
		prev = exec_next_command(d, &cur, &cur_c, 0);
	}
	return (prev);
}

int	run(t_data *d, int start, int end, char **envp)
{
	int		return_val;

	if (!d->input)
		return (0);
	d->command = ft_substr(d->input, start, end - start);
	d->tokens = split_args(d);
	ft_convert_envs(d);
	merge_tokens(*d->tokens, 0);
	convert_wildcards(d->tokens);
	merge_tokens(*d->tokens, 1);
	free(d->command);
	return_val = exec_commands(d, envp);
	t_clear(d->tokens);
	free(d->tokens);
	return (return_val);
}
