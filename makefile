CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LIBFT = ./libft
NAME_CLIENT = client
NAME_SERVER = server

LIBS = $(LIBFT)/libft.a

SRC_CLIENT = client.c
SRC_SERVER = server.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

all: $(LIBFT)/libft.a $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

%.o: %.c client.h
	@$(CC) $(CFLAGS) -o $@ -C $<

$(NAME_CLIENT): $(OBJ_CLIENT)
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBS) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	@$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBS) -o $(NAME_SERVER)

clean:
	@rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME_CLIENT) $(NAME_SERVER)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re