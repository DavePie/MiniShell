CFILES	:= *.c
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

re: fclean all

run: all
	./minishell

.PHONY: clean fclean all re run

