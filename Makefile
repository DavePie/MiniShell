# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 18:04:17 by dvandenb          #+#    #+#              #
#    Updated: 2023/11/30 18:04:21 by dvandenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCDIR	:= src
CFILES	:= verify_input.c utils.c utils_shell.c main.c logic.c list_utils2.c list_utils.c \
history.c builtin.c builtin2.c create_tokens.c wildcards.c convert_env.c commands.c pipe.c \
wildcards2.c verify_input2.c pipe2.c commands2.c convert_env2.c export_env.c export_env2.c builtin3.c
CFILES	:= $(patsubst %,$(SRCDIR)/%,$(CFILES))

RM		:= rm -f
NAME	:= minishell
CC		:= gcc
INCDIR	:= -I includes -I libft

LIB		:= libft.a
LIBDIR	:= libft
LIBPATH	:= $(LIBDIR)/$(LIB)
CFLAGS	:= -Wall -Wextra -Werror -fsanitize=address
READLINE_LIB_DIR :=

ifeq ($(shell uname -s),Darwin)
    INCDIR := $(INCDIR) -I $(HOME)/.brew/Cellar/readline/8.1.1/include
	READLINE_LIB_DIR := -L $(HOME)/.brew/opt/readline/lib
endif

all: $(NAME)

$(NAME): $(CFILES) $(LIBPATH)
	$(CC) $(CFLAGS) $(CFILES) $(INCDIR) -o $(NAME) -lreadline $(READLINE_LIB_DIR) $(LIBPATH)

$(LIBPATH):
	make -C $(LIBDIR)

clean:
	make -C $(LIBDIR) clean

fclean: clean
	$(RM) $(LIBPATH)
	make -C $(LIBDIR) clean
	$(RM) $(NAME)

re: fclean all

run: all
	./minishell

leaks: all
	leaks --atExit -- ./minishell

.PHONY: clean fclean all re run

