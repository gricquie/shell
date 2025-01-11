NAME = shell

SRCS =	main.c \
	readcmd.c \
	readline.c \
	stdin_handler.c \
	stdin_helper.c \
	cntrfuncs.c \

HEADER = shell.h \
	 stdin_helper.h \
	 cntrfuncs.h \

HEADERLIBFT = libft.h

OBJS = $(SRCS:.c=.o)

SRCSDIR = srcs/
OBJDIR = objs/
HEADERDIR = includes/
LIBFTDIR = libft/

HEADERFULL = $(addprefix $(HEADERDIR), $(HEADER))

OBJFULL = $(addprefix $(OBJDIR), $(OBJS))

FLAGS = -Werror -Wextra -Wall -ggdb

all : $(NAME)

$(NAME) : $(OBJFULL) $(addprefix $(HEADERDIR), $(HEADER)) $(addprefix $(LIBFTDIR), $(HEADERLIBFT))
	gcc -o $(NAME) $(OBJFULL) -I $(HEADERDIR) -L $(LIBFTDIR) -lft -lncurses

$(OBJDIR)%.o : $(SRCSDIR)%.c $(HEADERFULL)
	mkdir $(OBJDIR) 2> /dev/null || true
	gcc -o $@ -c $< $(FLAGS) -I $(HEADERDIR) -I $(LIBFTDIR) -L $(LIBFTDIR) -lft -lncurses

clean :
	rm -f $(OBJFULL)
	rmdir $(OBJDIR) 2> /dev/null || true

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
