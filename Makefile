CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT = ./libft
NAME_CLIENT = ./mandatory/client
NAME_SERVER = ./mandatory/server
NAME_CLIENT_BONUS = ./bonus/client
NAME_SERVER_BONUS = ./bonus/server

LIBS = $(LIBFT)/libft.a

SRC_CLIENT = ./mandatory/client.c
SRC_SERVER = ./mandatory/server.c

SRC_CLIENT_BONUS = ./bonus/client_bonus.c
SRC_SERVER_BONUS = ./bonus/server_bonus.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)

all: $(LIBFT)/libft.a $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

%.o: %.c 
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME_CLIENT): $(OBJ_CLIENT)
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBS) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	@$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBS) -o $(NAME_SERVER)

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS) $(LIBFT)/libft.a
	@$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) $(LIBS) -o $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(OBJ_SERVER_BONUS) $(LIBFT)/libft.a
	@$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) $(LIBS) -o $(NAME_SERVER_BONUS)

clean:
	@rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	@rm -f $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME_CLIENT) $(NAME_SERVER)
	@rm -f $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)
	@make -C $(LIBFT) fclean

re: fclean all

bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

.PHONY: all clean fclean re bonus