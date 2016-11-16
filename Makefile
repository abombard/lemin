CC=clang
FLAGS=
FLAGS42=-Wall -Wextra -Werror -Wconversion

NAME=lemin
TEST=test.sh

LIBS_DIR=./libs
DIR_LIBFT=$(LIBS_DIR)/libft
DIR_PRINTF=$(LIBS_DIR)/printf
DIR_LIST=$(LIBS_DIR)/list

LIBS=-L $(DIR_PRINTF) -lprintf -L $(DIR_LIBFT) -lft -L $(DIR_LIST) -llist

SRC_DIR=srcs
INCLUDES=-I ./ -I ./includes -I $(DIR_LIBFT) -I $(DIR_LIST) -I $(DIR_PRINTF)

BUILD_DIR=__build

SRC=\
	lemin.c\
	parser.c\
	parser__stream.c\
	parser__state_get.c\
	parser__state_check.c\
	parser__tokens_get.c\
	lemin__room.c\
	lemin__room_show.c\
	rate_graph.c\
	path.c\
	get_paths.c\


OBJ=$(addprefix $(BUILD_DIR)/,$(SRC:.c=.o))

all:$(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	@mkdir -p $@

exec:
	@make -C $(DIR_LIBFT)
	@make -C $(DIR_PRINTF)
	@make -C $(DIR_LIST)

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): exec $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $@
	@echo "$@ was created"

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)
	@make $@ -C $(DIR_LIBFT)
	@make $@ -C $(DIR_PRINTF)
	@make $@ -C $(DIR_LIST)

re: fclean all

test: $(NAME)
