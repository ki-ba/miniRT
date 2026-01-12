# BASIC #

NAME = miniRT
TEST_NAME = run_tests
CC = cc
DEPS = $(OBJ:.o=.d)

# COMPILATION FLAGS #

CFLAGS = -Wall -Wextra -Werror -g3 -MMD -O3
INCLUDES = -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(VECTORS_DIR)/inc/
TEST_INCLUDES = -IUnity/src/
LIBS = -L$(MLX_DIR) -lmlx -lX11 -lXext -L$(LIBFT_DIR) -lft -lm -L$(VECTORS_DIR) -lvectors

# DIRECTORIES #

LIB_DIR = ./libs/
SRC_DIR = src/
OBJ_DIR = .obj/
INC_DIR = inc/
TEST_DIR = tests/
MLX_DIR = $(LIB_DIR)minilibx-linux/
LIBFT_DIR = $(LIB_DIR)libft/
VECTORS_DIR = $(LIB_DIR)vectors/

# SUBDIRS #

PARSING_DIR		= parsing/
OBJECTS_DIR		= objects/
VEC3_DIR		= vec3/
DEBUG_DIR		= debug/
GRAPHICS_DIR	= graphics/
CORE_DIR		= core/
RENDER_DIR		= render/
COLOR_DIR		= color/

SUBDIRS = $(PARSING_DIR) $(OBJECTS_DIR) $(VEC3_DIR) $(DEBUG_DIR) $(GRAPHICS_DIR) $(CORE_DIR) $(RENDER_DIR) $(COLOR_DIR)
TEST_SUBDIRS = $(addprefix tests/, $(SUBDIRS))

# SOURCE FILES #

PARSING_FILENAMES 	= parsing.c parsing_utils.c read_properties.c str_utils.c
OBJECTS_FILENAMES 	= objects.c
VEC3_FILENAMES		= vec3_create.c vec3_add.c vec3_cross.c vec3_dot.c vec3_scale.c vec3_normalize.c vec3_substract.c vec3_magnitude.c
DEBUG_FILENAMES		= debug.c debug_utils.c
GRAPHICS_FILENAMES	= graphics.c
CORE_FILENAMES		= core.c hooks.c math.c
RENDER_FILENAMES	= render.c
COLOR_FILENAMES		= color.c

# CATEGORY_FILENAMES = filename.c

PARSING_SRC 	= $(addprefix $(SRC_DIR)$(PARSING_DIR), $(PARSING_FILENAMES))
OBJECTS_SRC 	= $(addprefix $(SRC_DIR)$(OBJECTS_DIR), $(OBJECTS_FILENAMES))
VEC3_SRC		= $(addprefix $(SRC_DIR)$(VEC3_DIR), $(VEC3_FILENAMES))
DEBUG_SRC		= $(addprefix $(SRC_DIR)$(DEBUG_DIR), $(DEBUG_FILENAMES))
GRAPHICS_SRC	= $(addprefix $(SRC_DIR)$(GRAPHICS_DIR), $(GRAPHICS_FILENAMES))
CORE_SRC		= $(addprefix $(SRC_DIR)$(CORE_DIR), $(CORE_FILENAMES))
RENDER_SRC		= $(addprefix $(SRC_DIR)$(RENDER_DIR), $(RENDER_FILENAMES))
COLOR_SRC		= $(addprefix $(SRC_DIR)$(COLOR_DIR), $(COLOR_FILENAMES))
# CATEGORY_FULL_SRC = addprefix CATEGORY SOURCE_LIST

SRC = $(PARSING_SRC) $(OBJECTS_SRC) $(VEC3_SRC) $(DEBUG_SRC) $(DESTROY_SRC) $(GRAPHICS_SRC) $(CORE_SRC) $(RENDER_SRC) $(COLOR_SRC)
# add CAT_SRC here if a new category is added

TEST_SRC = $(subst $(SRC_DIR), $(TEST_DIR), $(SRC:%.c=%_test.c))

#NOTE: SRC and TEST_SRC do NOT contain main.c and test runner files. They have to be added separately in the rules.
#NOTE: Consequently, OBJ and TEST_OBJ also do not contain main.o and test.o files.

# OBJECT FILES #

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)%.c=$(OBJ_DIR)$(TEST_DIR)%.o) $(OBJ_DIR)$(TEST_DIR)unity.o



#NOTE: by default, both miniRT and the tests are built when 'make' is run.
#NOTE: to only build miniRT, run 'make miniRT' instead.

# PHONY RULES #

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
	$(MAKE) -C $(VECTORS_DIR) fclean
	rm -f $(NAME)

.PHONY : re
re: fclean all

.PHONY : objdirs
objdirs:
	mkdir -p $(addprefix $(OBJ_DIR), $(SUBDIRS))
	mkdir -p $(addprefix $(OBJ_DIR), $(TEST_SUBDIRS))

# LIBRARIES #

MLX_LIB = $(MLX_DIR)libmlx.a
LIBFT_LIB = $(LIBFT_DIR)libft.a
VECTORS_LIB = $(VECTORS_DIR)libvectors.a

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

${VECTORS_LIB}:
	$(MAKE) -C $(VECTORS_DIR)

# ACTUAL RULES #

$(TEST_NAME): $(TEST_OBJ) $(OBJ) $(OBJ_DIR)$(TEST_DIR)test.o | $(MLX_LIB) $(LIBFT_LIB) objdirs
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_INCLUDES) $(OBJ) $(OBJ_DIR)$(TEST_DIR)test.o $(TEST_OBJ) $(LIBS) -o $(TEST_NAME)
	./$(TEST_NAME)


$(NAME) : $(OBJ) .obj/main.o $(MLX_LIB) $(LIBFT_LIB) $(VECTORS_LIB) |  objdirs
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(OBJ_DIR)main.o $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)tests/%.o : $(TEST_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_INCLUDES) -c $< -o $@

$(OBJ_DIR)tests/unity.o : Unity/src/unity.c Unity/src/unity.h
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -c $< -o $@

-include $(DEPS)
