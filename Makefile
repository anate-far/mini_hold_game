# === Variables ===
NAME		= bin/mini_hold_game

CC			= cc
CFLAGS		=  -g -Wall -Wextra -Werror -Iinclude

SRC_DIR		= src
OBJ_DIR		= bin

SRC_FILES	= main.c map.c entitie.c ft_lib.c
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# === Règles ===

all: $(NAME)

# Création de l'exécutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compilation des .o vers le dossier bin/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer les .o
clean:
	rm -rf $(OBJ_DIR)/*.o

# Nettoyer les .o + exécutable
fclean: clean
	rm -f $(NAME)

# Recompiler proprement
re: fclean all

.PHONY: all clean fclean re
