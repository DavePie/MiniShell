/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:06:33 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/30 15:59:10 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

//need calloc, strlen, free_str_tab

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "commands.h"

char	*ft_free(char *s);

char	*check_access(char **paths, char *cmd);

char	*get_command_path(char *cmd, t_export **exports);

/**
 * @brief (might be unnecessary) verif if fd != -1 and closes it
 * 
 * @param fd 
 */
void	ft_close(int fd);
/**
 * @brief duplicates fd1 to fd2 and closes fd1
 * 
 * @param fd1 
 * @param fd2 
 */
void	ft_dup2(int fd1, int fd2);

char	*join_path_with_cmd(const char *path, const char *cmd);

/**
 * @brief executes child routine
 * @brief closes pipefd[0] and duplicates pipefd[1] to STDOUT_FILENO 
 * @brief and calls ft_exec_command
 * 
 * @param pipefd 
 * @param cmd 
 * @param envp 
 */
void	ft_child(int *pipefd, t_com *cmd, t_data *d);

/**
 * @brief executes parent routine
 * @brief closes pipefd[1], waits forr child to finish and returns pipefd[0]
 * 
 * @param pipefd 
 * @param prev_input_fd 
 * @param child_pid 
 * @return int 
 */
int		ft_parent(int *pipefd, t_com *cmd, pid_t child_pid);

/**
 * @brief creates the pipe and the fork, if child dups prev_input_fd
 * to STDIN_FILENO,
 * @brief if parent calls ft_parent assigning the return value
 * to prev_input_fd
 * 
 * @param prev_input_fd 
 * @param cmd 
 * @param envp 
*/
int		ft_fork_and_exec(t_data *d, t_com *cmd);

#endif