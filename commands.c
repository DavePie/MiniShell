/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:40:46 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/22 16:32:16 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
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
// void	ft_error(char *s)
// {
// 	printf("%s\n", s);
// }
// void	ft_close(int fd)
// {
// 	if (fd != -1)
// 		close(fd);
// }

// void	ft_dup2(int fd1, int fd2)
// {
// 	dup2(fd1, fd2);
// 	ft_close(fd1);
// }
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

void	set_cmd_args(t_token *cur, int l, t_com *cur_c)
{
	char	**args;
	int		prev;
	int		i;

	args = malloc(sizeof(char *) * (l + 1));
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
}

int	open_fd(char *name, int prev, int tags, int mode)
{
	int	fd;

	if (prev > 0)
		close(prev);
	fd = open(name, tags, mode);
	// error out if -1
	return (fd);
}
void	ft_c(int *pipefd, char *input)
{
	ft_close(pipefd[0]);
	ft_dup2(pipefd[1], STDOUT_FILENO);
	printf("%s", input);
	exit(0);
}

int	ft_p(int *pipefd, pid_t child_pid)
{
	ft_close(pipefd[1]);
	waitpid(child_pid, NULL, 0);
	return (pipefd[0]);
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
		ft_c(pipefd, input);
	return ft_p(pipefd, pid);
}

int	exec_next_command(t_token **cur, t_com *cmd)
{
	int		l;
	t_token	*first;

	first = *cur;
	l = 0;
	while (*cur)
	{
		if (type_t(*cur) == OUT)
			cmd->o_fd = open_fd((*cur)->next->token,
					cmd->o_fd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (type_t(*cur) == OUT_A)
			cmd->o_fd = open_fd((*cur)->next->token,
					cmd->o_fd, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (type_t(*cur) == IN)
			cmd->i_fd = open_fd((*cur)->next->token, cmd->i_fd, O_RDONLY, 0);
		else if (type_t(*cur) == IN_D)
			cmd->i_fd = exec_redir((*cur)->next->token);
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
	return (ft_fork_and_exec(cmd)); // return run command
}

int	exec_commands(t_token **first, char **envp)
{
	t_token	*cur;
	t_com	cur_c;
	int		prev;

	cur = *first;
	prev = NO_INPUT;
	while (cur)
	{
		cur_c = (t_com){.env = envp, .i_fd = prev, .o_fd = OUTPUT_STD};
		prev = exec_next_command(&cur, &cur_c);
	}
	return (prev); // last command output.
}
