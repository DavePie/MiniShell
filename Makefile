CFILES	:= verify_input.c utils.c utils_shell.c main.c logic.c list_utils2.c list_utils.c history.c builtin.c create_tokens.c run_command.c wildcards.c convert_env.c commands.c pipe.c
RM		:= rm -f
NAME	:= minishell
CC		:= gcc
INCDIR	:= -I . -I libft -I $(HOME)/.brew/Cellar/readline/8.1.1/include

LIB	:= libft.a
LIBDIR := libft
LIBPATH := $(LIBDIR)/$(LIB)
CFLAGS	:= -Wall -Wextra -Werror $(INCDIR) #-fsanitize=address 

all: $(NAME)

$(NAME): $(CFILES) $(LIBPATH)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME) -lreadline -L$(HOME)/.brew/opt/readline/lib $(LIBPATH)

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

