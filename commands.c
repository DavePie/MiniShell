/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:40:46 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/24 13:08:34 by dvandenb         ###   ########.fr       */
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

int	reallojoin(char **dest, int cur_size, char *src, int src_size)
{
	char	*temp;
	int		i;

	i = -1;
	temp = (char *)malloc(sizeof(char) * (cur_size + src_size + 1));
	if (!temp)
		return (0);
	while (++i < cur_size)
		temp[i] = (*dest)[i];
	while (i < cur_size + src_size)
	{
		temp[i] = src[i - cur_size];
		i++;
	}
	temp[i] = '\0';
	free(*dest);
	*dest = temp;
	return (cur_size + src_size);
}

char	*read_delimiter(char *del)
{
	char	*input;
	char	*ans;

	input = readline("> ");
	ans = ft_calloc(1, sizeof(char));
	while (ft_strcmp(input, del))
	{
		reallojoin(&ans, ft_strlen(ans), input, ft_strlen(input));
		reallojoin(&ans, ft_strlen(ans), "\n", 1);
		free(input);
		input = readline("> ");
	}
	return (ans);
}

int	exec_redir(char *delim)
{
	int		pipefd[2];
	pid_t	pid;
	char	*input;

	if (pipe(pipefd) == -1)
		ft_error("Pipe error");
	pid = fork();
	if (pid == -1)
		ft_error("Fork error");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		input = read_delimiter(delim);
		ft_close(pipefd[0]);
		ft_dup2(pipefd[1], STDOUT_FILENO);
		printf("%s", input);
		exit(EXIT_SUCCESS);
	}
	ft_close(pipefd[1]);
	waitpid(pid, NULL, 0);
	return (pipefd[0]);
}
