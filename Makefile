# BASIC #

NAME = miniRT
CC = cc

# DIRECTORIES #

LIB_DIR = ./libs/
MLX_DIR = $(LIB_DIR)minilibx-linux/
LIBFT_DIR = $(LIB_DIR)libft/
SRC_DIR = src/
OBJ_DIR = .obj/
INC_DIR = inc/

# SUBDIRS #

PARSING_DIR = parsing/

SUBDIRS = $(PARSING_DIR)
# SOURCE FILES #

BASIC_SRC = main.c
PARSING_SRC = parsing.c
# CATEGORY_SRC = filename.c

PARSING_FULL_SRC = $(addprefix $(SRC_DIR)$(PARSING_DIR), $(PARSING_SRC))
# CATEGORY_FULL_SRC = addprefix CATEGORY SOURCE_LIST

BASIC_FULL_SRC = $(addprefix $(SRC_DIR), $(BASIC_SRC))

SRC = $(PARSING_FULL_SRC) $(BASIC_FULL_SRC)
# add X_FULL_SRC here ---^


# OBJECT FILES #

OBJ = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:%.c=%.o))

# COMPILATION FLAGS #
CFLAGS = -Wall -Wextra -Werror -g -MMD
INCLUDES = -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)
LIBS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft

# LIBRARIES #
MLX_LIB = $(MLX_DIR)libmlx.a
LIBFT_LIB = $(LIBFT_DIR)libft.a

# RULES #
.PHONY : all
all: objdirs $(NAME)

.PHONY : clean
clean:
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

.PHONY : fclean
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) fclean
	rm -f $(NAME)

.PHONY : re
re: fclean all

objdirs:
	mkdir -p $(OBJ_DIR)$(SUBDIRS)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME) : $(OBJ) | $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
