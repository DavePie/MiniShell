/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:08:01 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/24 13:08:53 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "libft.h"
#include "utils.h"
#include "commands.h"
#include "utils_shell.h"
#include "error_codes.h"

static char	*check_access(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = join_path_with_cmd(paths[i], cmd);
		if (!full_path)
			continue ;
		if (access(full_path, X_OK) == 0)
			return (full_path);
		full_path = ft_free(full_path);
		i++;
	}
	return (NULL);
}

static char	*get_command_path(char *cmd)
{
	char	*path_env;
	char	*cmd_path;
	char	**paths;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else if (access(cmd, F_OK) == 0 && !ft_perror(cmd))
		exit(EXIT_PERM_DENIED);
	path_env = getenv("PATH");
	if (!path_env)
		ft_error("PATH variable not found.");
	paths = ft_split(path_env, ':');
	if (!paths)
		ft_error("Split error on PATH variable.");
	cmd_path = check_access(paths, cmd);
	ft_free_str_tab(paths);
	if (!cmd_path)
		ft_perror(cmd);
	if (!cmd_path)
		exit(EXIT_CMD_NOT_FOUND);
	return (cmd_path);
}

/**********************************************************/
void	ft_child(int *pipefd, t_com *cmd)
{
	char	*path;

	ft_close(pipefd[0]);
	if (cmd->o_fd == OUTPUT_PIPE)
		ft_dup2(pipefd[1], STDOUT_FILENO);
	if (cmd->o_fd != OUTPUT_STD)
		ft_dup2(cmd->o_fd, STDOUT_FILENO);
	if (cmd->args[0])
	{
		path = get_command_path(cmd->args[0]);
		execve(path, cmd->args, cmd->env);
		ft_perror(cmd->args[0]);
		path = ft_free(path);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	ft_parent(int *pipefd, t_com *cmd, pid_t child_pid)
{
	int	return_val;
	int	pid;

	ft_close(pipefd[1]);
	if (cmd->i_fd)
		ft_close(cmd->i_fd);
	if (cmd->o_fd != OUTPUT_PIPE)
	{
		waitpid(child_pid, &return_val, WCONTINUED);
		pid = 0;
		while (pid >= 0)
			pid = wait(NULL);
	}
	if (cmd->o_fd != OUTPUT_PIPE)
		return (return_val);
	return (pipefd[0]);
}

int	ft_fork_and_exec(t_com *cmd)
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
		signal(SIGINT, SIG_DFL);
		if (cmd->i_fd > 0)
			ft_dup2(cmd->i_fd, STDIN_FILENO);
		if (cmd->i_fd != -1)
			ft_child(pipefd, cmd);
		exit(EXIT_FAILURE);
	}
	free(cmd->args);
	return (ft_parent(pipefd, cmd, pid));
}
