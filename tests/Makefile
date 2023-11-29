CFILES	:= main.c
RM		:= rm -f
NAME	:= tests
CC		:= gcc
INCDIR	:= -I .

LIB	:= libft.a
BIN    := minishell
LIBDIR := ../libft
BINDIR := ..
LIBPATH := $(LIBDIR)/$(LIB)
BINPATH := $(BINDIR)/$(BIN)
CFLAGS	:= -Wall -Wextra -Werror $(INCDIR) #-fsanitize=address 

all: $(NAME)

$(NAME): $(CFILES) $(LIBPATH) $(BIN)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME) $(LIBPATH)

$(LIBPATH):
	make -C $(LIBDIR)

$(BINPATH):
	make -C $(BINDIR)

$(BIN): $(BINPATH)
	cp $(BINPATH) $(BIN)
clean:
	make -C $(LIBDIR) clean
	make -C $(BINDIR) clean

fclean: clean
	$(RM) $(LIBPATH)
	make -C $(LIBDIR) fclean
	$(RM) $(NAME)
	make -C $(BINDIR) fclean

re: fclean all

run: all
	./$(NAME)

leaks: all
	leaks --atExit -- ./$(NAME)

.PHONY: clean fclean all re run

