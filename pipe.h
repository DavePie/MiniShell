/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:06:33 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/13 14:35:04 by alde-oli         ###   ########.fr       */
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

/**
 * @brief verifies if there are enough args, if envp exists 
 * @brief and if input and output are usable
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 */
void	ft_start_check(int argc, char **argv, char **envp);
/**
 * @brief executes the command
 * @note will need adjustments for builtins 
 * 
 * @param cmd 
 * @param envp 
 * @return int 
 */
int		ft_exec_command(char *cmd, char **envp);
/**
 * @brief executes child routine
 * @brief closes pipefd[0] and duplicates pipefd[1] to STDOUT_FILENO 
 * @brief and calls ft_exec_command
 * 
 * @param pipefd 
 * @param cmd 
 * @param envp 
 */
void	ft_child(int *pipefd, char *cmd, char **envp);
/**
 * @brief executes parent routine
 * @brief closes pipefd[1], waits forr child to finish and returns pipefd[0]
 * 
 * @param pipefd 
 * @param prev_input_fd 
 * @param child_pid 
 * @return int 
 */
int		ft_parent(int *pipefd, int *prev_input_fd, pid_t child_pid);
/**
 * @brief creates the pipe and the fork, if child dups prev_input_fd to STDIN_FILENO,
 * @brief if parent calls ft_parent assigning the return value to prev_input_fd
 * 
 * @param prev_input_fd 
 * @param cmd 
 * @param envp 
*/
void	ft_fork_and_exec(int *prev_input_fd, char *cmd, char **envp);
/**
 * @brief calls ft_start_check, opens infile, loops ft_fork_and_exec until last command
 * @brief opens outfile, dups outfile to STDOUT_FILENO and calls ft_exec_command
 * 
 * @param arg_nb 
 * @param args 
 * @param envp 
 * @return int 
 */
int		ft_pipe(int arg_nb, char **args, char **envp);

#endif