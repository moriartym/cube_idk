CC = cc

CFLAGS_NORMAL = 
#-Wall -Wextra -Werror

NAME = cub3d

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

SRCS_NORMAL = get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		cub3d.c \
		map_validation/extract_map.c \
		map_validation/extract_elements.c \
		map_validation/extract_content.c \
		map_validation/check_map.c \
		map_validation/check_map_utils.c \
		error_handling/handle_error.c \
		window/window.c \
		window/window_utils.c \
		window/init_struct.c \
		minimap/minimap.c \
		player/player.c \
		movement/movement.c \
		movement/update_movement.c \
		movement/movement_helper.c \
		raycast/raycast.c \
		raycast/raycast_3d.c \
		raycast/raycast_helper.c \
		raycast/enemy_sprites.c \
		enemy/enemy.c \

OBJS = $(SRCS_NORMAL:.c=.o)

all: $(NAME)

bonus: $(NAME)

# DELETE THIS BEFORE SUBMISSION
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    MLX_FLAGS = -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else ifeq ($(UNAME_S),Darwin)
    MLX_FLAGS = -Lminilibx-linux -lmlx -framework OpenGL -framework AppKit
endif

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS_NORMAL) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
