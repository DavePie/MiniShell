/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:30:27 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/22 16:58:22 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "libft.h"
#include "utils.h"
#include "commands.h"

//TEMP
 char	*ft_free(char *s)
{
	if (s)
		free(s);
	s = 0;
	return (0);
}
//TEMP
 void	ft_error(char *s)
{
	printf("%s\n", s);
}

 void	ft_close(int fd)
{
	if (fd != -1)
		close(fd);
}

 void	ft_dup2(int fd1, int fd2)
{
	dup2(fd1, fd2);
	ft_close(fd1);
}

void	ft_start_check(int argc, char **argv, char **envp)
{
	int	i;

	if (argc < 5)
		ft_error("Usage: ./pipex file1 cmd1 ... cmdn file2");
	if (envp == NULL || *envp == NULL)
		ft_error("Environment variables are not provided.");
	if (access(argv[1], R_OK) == -1)
		ft_error("Error with file1");
	i = 2;
	while (i < argc - 2)
	{
		if (argv[i] == NULL || *argv[i] == '\0')
			ft_error("Command is empty or null.");
		i++;
	}
	if (access(argv[argc - 1], F_OK) != -1
		&& access(argv[argc - 1], W_OK) == -1)
		ft_error("Error with file2");
}

/**********************************************************************/
static char	*ft_getenv(const char *name, char **env)
{
	int		i;
	int		name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

static char	*join_path_with_cmd(const char *path, const char *cmd)
{
	char	*full_path;
	size_t	path_len;
	size_t	cmd_len;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	full_path = ft_calloc(sizeof(char), (path_len + cmd_len + 2));
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, (char *)path);
	full_path[path_len] = '/';
	ft_strcpy(&full_path[path_len + 1], (char *)cmd);
	full_path[path_len + cmd_len + 1] = '\0';
	return (full_path);
}

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

static char	*get_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	*cmd_path;
	char	**paths;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = ft_getenv("PATH", envp);
	if (!path_env)
		ft_error("PATH variable not found.");
	paths = ft_split(path_env, ':');
	if (!paths)
		ft_error("Split error on PATH variable.");
	cmd_path = check_access(paths, cmd);
	ft_free_str_tab(paths);
	if (!cmd_path)
		ft_error("Command not found: ");
	return (cmd_path);
}

int	ft_exec_command(char **cmd, char **envp)
{

	char	*path;

	path = get_command_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
		ft_error("Execve error");
	ft_free_str_tab(cmd);
	path = ft_free(path);
	return (1);
}

/**********************************************************/
void	ft_child(int *pipefd, t_com *cmd)
{
	ft_close(pipefd[0]);
	if (cmd->o_fd == OUTPUT_PIPE)
		ft_dup2(pipefd[1], STDOUT_FILENO);
	if (cmd->o_fd != OUTPUT_STD)
		ft_dup2(cmd->o_fd, STDOUT_FILENO);
	if (cmd->args[0])
		ft_exec_command(cmd->args, cmd->env);
	else
		exit(0);
}

int	ft_parent(int *pipefd, t_com *cmd, pid_t child_pid)
{
	int return_val;

	ft_close(pipefd[1]);
	if (cmd->i_fd)
		ft_close(cmd->i_fd);
	waitpid(child_pid, &return_val, 0);
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
		if (cmd->i_fd)
			ft_dup2(cmd->i_fd, STDIN_FILENO);
		ft_child(pipefd, cmd);
	}
	return ft_parent(pipefd, cmd, pid);
}

// int	ft_pipe(int argc, char **argv, char **envp)
// {
// 	int	i;
// 	int	input_fd;
// 	int	output_fd;

// 	ft_start_check(argc, argv, envp);
// 	input_fd = open(argv[1], O_RDONLY);
// 	if (input_fd == -1)
// 		ft_error("Error with file1");
// 	i = 2;
// 	while (i < argc - 2)
// 	{
// 		ft_fork_and_exec(&input_fd, argv[i], envp);
// 		i++;
// 	}
// 	ft_dup2(input_fd, STDIN_FILENO);
// 	output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (output_fd == -1)
// 		ft_error("Error with file2");
// 	ft_dup2(output_fd, STDOUT_FILENO);
// 	ft_exec_command(argv[argc - 2], envp);
// 	ft_close(input_fd);
// 	ft_close(output_fd);
// 	return (0);
// }