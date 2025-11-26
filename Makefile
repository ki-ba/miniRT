# BASIC #

NAME = miniRT
TEST_NAME = run_tests
CC = cc

# COMPILATION FLAGS #

CFLAGS = -Wall -Wextra -Werror -g -MMD
INCLUDES = -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)
TEST_INCLUDES = -IUnity/src/
LIBS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft

# DIRECTORIES #

LIB_DIR = ./libs/
SRC_DIR = src/
OBJ_DIR = .obj/
INC_DIR = inc/
TEST_DIR = tests/
MLX_DIR = $(LIB_DIR)minilibx-linux/
LIBFT_DIR = $(LIB_DIR)libft/

# SUBDIRS #

PARSING_DIR = parsing/
SUBDIRS = $(PARSING_DIR)
TEST_SUBDIRS = $(addprefix tests/, $(SUBDIRS))

# SOURCE FILES #

PARSING_FILENAMES = parsing.c
# CATEGORY_FILENAMES = filename.c

PARSING_SRC = $(addprefix $(SRC_DIR)$(PARSING_DIR), $(PARSING_FILENAMES))
# CATEGORY_FULL_SRC = addprefix CATEGORY SOURCE_LIST

SRC = $(PARSING_SRC)
# add CAT_SRC here if a new category is added

TEST_SRC = $(subst $(SRC_DIR), $(TEST_DIR), $(SRC:%.c=%_test.c))

#NOTE: SRC and TEST_SRC do NOT contain main.c and test runner files. They have to be added separately in the rules.
#NOTE: Consequently, OBJ and TEST_OBJ also do not contain main.o and test.o files.

# OBJECT FILES #

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)%.c=$(OBJ_DIR)$(TEST_DIR)%.o) $(OBJ_DIR)$(TEST_DIR)unity.o

# LIBRARIES #

MLX_LIB = $(MLX_DIR)libmlx.a
LIBFT_LIB = $(LIBFT_DIR)libft.a

# PHONY RULES #

#NOTE: by default, both miniRT and the tests are built when 'make' is run.
#NOTE: to only build miniRT, run 'make miniRT' instead.

.PHONY : all
all: objdirs $(NAME) $(TEST_NAME)

.PHONY : clean
clean:
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

#NOTE: mlx does not have a fclean rule, so we just run clean for it.

.PHONY : fclean
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(NAME)

.PHONY : re
re: fclean all

.PHONY : objdirs
objdirs:
	mkdir -p $(OBJ_DIR)$(SUBDIRS)
	mkdir -p $(OBJ_DIR)$(TEST_SUBDIRS)


# ACTUAL RULES #

$(TEST_NAME): $(TEST_OBJ) $(OBJ) $(OBJ_DIR)$(TEST_DIR)test.o | $(MLX_LIB) $(LIBFT_LIB) objdirs
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_INCLUDES) $(OBJ) $(OBJ_DIR)$(TEST_DIR)test.o $(TEST_OBJ) $(LIBS) -o $(TEST_NAME)
	./$(TEST_NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME) : $(OBJ) .obj/main.o | $(MLX_LIB) $(LIBFT_LIB) objdirs
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(OBJ_DIR)main.o $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)tests/%.o : $(TEST_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_INCLUDES) -c $< -o $@

$(OBJ_DIR)tests/unity.o : Unity/src/unity.c
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -c $< -o $@
