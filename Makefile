NAME		=	tetris
CC			=	cc
INCLUDE		=	-I./includes
FLAGS		=
# FLAGS		=	-Wall -Wextra -Werror -g -fsanitize=thread
RM			=	rm -rf

SRC_DIR		=	srcs
SRC			=	tetris.c

SRCS	= $(addprefix $(SRC_DIR)/, $(SRC))

OBJ_DIR	= objs
OBJS	= $(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(INCLUDE) $(SRCS) -lncurses -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $(@D)
	$(CC) $(FLAGS) $(INCLUDE) -o $@ -c $<

all: $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
