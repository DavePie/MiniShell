CFILES	:= verify_input.c utils.c utils_shell.c main.c logic.c list_utils2.c list_utils.c \
history.c builtin.c builtin2.c create_tokens.c wildcards.c convert_env.c commands.c pipe.c \
wildcards2.c verify_input2.c pipe2.c commands2.c convert_env2.c export_env.c export_env2.c
RM		:= rm -f
NAME	:= minishell
CC		:= gcc
INCDIR	:= -I includes -I libft -I $(HOME)/.brew/Cellar/readline/8.1.1/include

LIB		:= libft.a
LIBDIR	:= libft
LIBPATH	:= $(LIBDIR)/$(LIB)
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

