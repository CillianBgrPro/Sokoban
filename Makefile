NAME = sokoban

SRCS = main.c \
	board.c \
	init.c \

all: $(NAME)

$(NAME): $(SRCS)
	gcc $(SRCS) -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all