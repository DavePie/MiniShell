/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:40:46 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/23 16:15:48 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "commands.h"
#include "pipe.h"
#include "utils.h"

/*
File: directly after redir (< file), checked first.
	Files can't become commands. (cat < a < b, a isn't command)
	print can only error once, but still check rest of files
Command: is not before redir.
Pipes: Fake pipe if redir on command
Arg not redir but after command without pipe
*/

/**
 * @brief Get the type object
 * 
 * @param token 
 * @return int 
 */
int	type_t(t_token *token)
{
	if (token->is_string)
		return (0);
	if (!ft_strcmp(token->token, "|"))
		return (PIPE);
	if (!ft_strcmp(token->token, ">"))
		return (OUT);
	if (!ft_strcmp(token->token, ">>"))
		return (OUT_A);
	if (!ft_strcmp(token->token, "<"))
		return (IN);
	if (!ft_strcmp(token->token, "<<"))
		return (IN_D);
	return (0);
}

int	set_cmd_args(t_token *cur, int l, t_com *cur_c)
{
	char	**args;
	int		prev;
	int		i;

	args = malloc(sizeof(char *) * (l + 1));
	if (!args)
		return (0);
	args[l] = 0;
	prev = 0;
	i = 0;
	while (cur && type_t(cur) != PIPE)
	{
		if (!prev && !type_t(cur))
			args[i++] = cur->token;
		prev = type_t(cur);
		cur = cur->next;
	}
	cur_c->args = args;
	return (1);
}

int	exec_redir(char *input)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		ft_error("Pipe error");
	pid = fork();
	if (pid == -1)
		ft_error("Fork error");
	if (pid == 0)
	{
		ft_close(pipefd[0]);
		ft_dup2(pipefd[1], STDOUT_FILENO);
		printf("%s", input);
		exit(0);
	}
	ft_close(pipefd[1]);
	waitpid(pid, NULL, 0);
	return (pipefd[0]);
}

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
	return (fd);
}

int	exec_next_command(t_token **cur, t_com *cmd, int l)
{
	t_token	*first;

	first = *cur;
	while (*cur)
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
			break ;
		}
		if (type_t(*cur))
			(*cur) = (*cur)->next;
		else
			l++;
		(*cur) = (*cur)->next;
	}
	set_cmd_args(first, l, cmd);
	return (ft_fork_and_exec(cmd));
}
