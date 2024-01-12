NAME				=	cub3d

COMPILE				=	cc -fsanitize=address -g

MLX_LINUX_FLAGS		=	-ldl -pthread -lm
MLX_MAC_FLAGS		=	-framework Cocoa -framework OpenGL -framework IOKit
MLXINCLUDE			=	MLX42/build/libmlx42.a -Iinclude -lglfw

COLOR_RESET			=	\033[0m
COLOR_CYAN			=	\033[36m
COLOR_GREEN			=	\033[32m
COLOR_RED			=	\033[31m

INCLUDE				=	libft/
REPO_URL			=	https://github.com/codam-coding-college/MLX42.git
LOCAL_DIR			=	MLX42

UTILS				=	utils_main.c utils_free.c utils_map.c utils_cross.c utils_basic.c \
						utils_color.c utils_dda.c utils_image.c utils_detection.c utils_random.c \
						utils_math.c utils_minimap.c utils_init.c utils_free_helper.c

INIT				=	init_1.c init_2.c parse_map.c map_valid.c validation_helper.c

DDA					=	dda_horizontal.c dda_vertical.c dda_dist/part1.c dda_dist/part2.c dda_dist/part3.c

MINIMAP				=	minimap.c rays.c

ANIMATION			=	anim_pistol.c anim_torch.c

MOVEMENT			=	keyhooks.c movement.c wall_door_detection.c

SPLASHSCREEN		=	splash.c

SRCS				=	main.c \
						$(addprefix init/, $(INIT)) \
						$(addprefix minimap/, $(MINIMAP)) \
						$(addprefix utils/, $(UTILS)) \
						$(addprefix movement/, $(MOVEMENT)) \
						$(addprefix animation/, $(ANIMATION)) \
						$(addprefix dda/, $(DDA)) \
						$(addprefix splashscreen/, $(SPLASHSCREEN))

OBJS				=	$(addprefix srcs/,$(SRCS:.c=.o))

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLX_FLAGS := $(MLX_LINUX_FLAGS)
else ifeq ($(UNAME_S), Darwin)
	MLX_FLAGS := $(MLX_MAC_FLAGS)
else
	$(error Unsupported operating system: $(UNAME_S))
endif

all: $(NAME)

$(NAME): clone		$(INCLUDE) $(OBJS)
					@cd $(INCLUDE) && make
					@$(COMPILE) $(FLAGS) -o $(NAME) $(OBJS) -L$(INCLUDE) -lft $(LDFLAGS) $(MLXINCLUDE) $(MLX_FLAGS)
					@echo "$(COLOR_CYAN)[READY] $(NAME)$(COLOR_RESET)"
					@rm -rf $(OBJS)

%.o: %.c
					@$(COMPILE) $(FLAGS) -c $< -o $@
					@echo "$(COLOR_GREEN)[OK] $@$(COLOR_RESET)"

clone:
					@if [ -d $(LOCAL_DIR) ]; then \
						echo "Repository already cloned"; \
					else \
						echo "Clone and build mlx"; \
						git clone $(REPO_URL) $(LOCAL_DIR) && \
						cd $(LOCAL_DIR) && \
						cmake -B build && \
						cd build && \
						make; \
					fi

remove:				fclean
					@if [ -d $(LOCAL_DIR) ]; then \
						rm -rf $(LOCAL_DIR); \
					else \
						echo "$(LOCAL_DIR) does not exist"; \
					fi

clean:
					@echo "$(COLOR_RED)Cleanup cub3d.$(COLOR_RESET)"
					@rm -f $(OBJS)
					@echo "$(COLOR_RED)Cleanup libft.$(COLOR_RESET)"
					@cd $(INCLUDE) && make clean
					@echo "$(COLOR_GREEN)Cleanup completed.$(COLOR_RESET)"

fclean:				clean
					@echo "$(COLOR_RED)Full-Clean cub3d.$(COLOR_RESET)"
					@rm -f $(NAME)
					@echo "$(COLOR_RED)Full-Clean libft.$(COLOR_RESET)"
					@cd $(INCLUDE) && make fclean
					@echo "$(COLOR_GREEN)Full-Clean completed.$(COLOR_RESET)"

re:					fclean all

leak:
					@dorker make re
					dorker valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-limit=no ./cub3d maps/map.cub

rand:
					@clear
					@make
					./cub3d

test:
					@clear
					@make
					./cub3d maps/map.cub

test1:
					@clear
					@make
					./cub3d maps/map1.cub

test2:
					@clear
					@make
					./cub3d maps/map2.cub

test3:
					@clear
					@make
					./cub3d maps/test.cub

walls:
					@clear
					@make
					./cub3d maps/walls.cub

.PHONY:				all clean fclean re clone
