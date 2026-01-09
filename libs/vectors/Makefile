# --- VARS ---

NAME = libvectors.a
CC = cc
FLAGS = -Wall -Wextra -Werror -g

LIBS = -L$(P_LIBFT) -lft
INCLUDES = -I$(P_INC) -I$(P_LIBFT)
DEBUGFLAGS = $(FLAGS) -fsanitize=address
P_OBJ = .obj/
P_SRC = src/
P_INC = inc/
P_LIBFT = ../libft/
# --- SRC ---

SRC = add_element.c clear_vector.c grow_vector.c

# --- RULES ---

OBJ = $(addprefix $(P_OBJ), $(SRC:%.c=%.o))

.PHONY = all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

$(P_OBJ)%.o: $(P_SRC)%.c $(P_INC)vectors.h | $(P_OBJ)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(P_OBJ):
	mkdir $(P_OBJ)


clean:
	rm -rf $(P_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
