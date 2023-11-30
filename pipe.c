/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:30:27 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/30 13:57:12 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "libft.h"
#include "utils.h"
#include "commands.h"

char	*ft_free(char *s)
{
	if (s)
		free(s);
	s = 0;
	return (0);
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

char	*join_path_with_cmd(const char *path, const char *cmd)
{
	char	*full_path;
	size_t	path_len;
	size_t	cmd_len;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	full_path = ft_calloc(sizeof(char), (path_len + cmd_len + 2));
	if (!full_path)
		exit_shell(1, "unable to allocate space");
	ft_strcpy(full_path, (char *)path);
	full_path[path_len] = '/';
	ft_strcpy(&full_path[path_len + 1], (char *)cmd);
	full_path[path_len + cmd_len + 1] = '\0';
	return (full_path);
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