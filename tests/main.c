/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:08:50 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/29 17:10:11 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

typedef struct s_test{
	const char	*cmds[100];
	const char	*outputs[100];
	const char	*description;
}	t_test;

void test_case(const char **input,
	const char **output, const char *description)
{
	int		fd;
	int		fdout;
	char	*test_output;
	char	*line_output;
	int		i;

	i = 1;
	test_output = 0;
	fd = open("./testfile", O_WRONLY | O_CREAT | O_TRUNC);
	while (*input)
	{
		write(fd, *input, ft_strlen(*input));
		write(fd, "\n", 1);
		input++;
	}
	close(fd);
	system("./minishell > outputfile < testfile");
	fdout = open("./outputfile", O_RDONLY);
	line_output = get_next_line(fdout);
	printf("Test group: %s\n", description);
	while (line_output && *output)
	{
		if (!ft_strnstr(line_output, "minishell$", ft_strlen(line_output)))
		{
			reallojoin(&test_output, ft_strlen(test_output),
				line_output, ft_strlen(line_output));
		}
		else if (test_output)
		{
			printf("Test %d ", i);
			if (ft_strncmp(test_output, *output, ft_strlen(test_output)))
			{
				printf("\033[0;31m[KO]\033[0;0m\n");
				printf("got:      <%s>\n", test_output);
				printf("expected: <%s>\n", *output);
			}
			else
			{
				printf("\033[0;32m[OK]\033[0;0m\n");
			}
			output++;
			i++;
			test_output = 0;
		}
		line_output = get_next_line(fdout);
	}
	if (test_output)
	{
		printf("Test %d ", i);
		if (ft_strncmp(test_output, *output, ft_strlen(test_output)))
		{
			printf("\033[0;31m[KO]\033[0;0m\n");
			printf("got:      <%s>\n", test_output);
			printf("expected: <%s>\n", *output);
		}
		else
		{
			printf("\033[0;32m[OK]\033[0;0m\n");
		}
		output++;
		i++;
		test_output = 0;
	}
	if (*output)
	{
		printf("\033[0;31m[KO]\033[0;0m\n");
		printf("got:      <%s>\n", "[nothing]");
		printf("expected: <%s>\n", *output);
	}
	while (line_output)
		line_output = get_next_line(fdout);
	close(fdout);
}



int	main(void)
{
	const t_test	test[100] = {
		(t_test){
		.cmds = {"echo test", "echo a b c", 0},
		.outputs = {"test\n", "a b c\n", 0},
		.description = "echo print argument"},
		(t_test){
		.cmds = {"\"e\"c'h'o 	\"t\"es't'", "   	 ech'o'	 a 	'b  c'", 0},
		.outputs = {"test\n", "a b  c\n", 0},
		.description = "in strings and spaces"},
		(t_test){
		.cmds = {"cat | wc -l | tr -d ' '", "abc", "ok", 0},
		.outputs = {"2\n", 0},
		.description = "test pipes and input"},
		(t_test){
		.cmds = {"cat | wc -l | tr -d ' '", 0},
		.outputs = {"0\n", 0},
		.description = "test pipes and input (stdin empty)"},
		(t_test){
		.cmds = {"$a | echo", 0},
		.outputs = {"\n", 0},
		.description = "Empty arg Pipe"},
		(t_test){
		.cmds = {"echo $a", 0},
		.outputs = {"\n", 0},
		.description = "Empty arg empty"},
		(t_test){
		.cmds = {"echo test && echo hello | cat", 0},
		.outputs = {"test\nhello\n", 0},
		.description = "mix pipes and logic"},
		(t_test){
		.cmds = {"echo $d $a $x", 0},
		.outputs = {"\n", 0},
		.description = "empty args empty"},
		(t_test){.cmds = {0}}
	};
	int				i;

	i = -1;
	while (test[++i].cmds[0])
	{
		test_case((const char **)test[i].cmds,
			(const char **)test[i].outputs, test[i].description);
	}
	return (0);
}