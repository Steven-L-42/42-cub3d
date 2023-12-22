NAME				=	cub3d

COMPILE				=	cc

#FLAGS				=	-Wall -Wextra -Werror

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

SRCS				=	srcs/test.c srcs/get_map.c srcs/utils.c srcs/ray_distance.c

OBJS				=	$(SRCS:.c=.o)

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
					@echo "$(COLOR_CYAN)Kompilierung abgeschlossen: $(NAME)$(COLOR_RESET)"
					@rm -rf $(OBJS)

%.o: %.c
					@$(COMPILE) $(FLAGS) -c $< -o $@
					@echo "$(COLOR_GREEN)Kompilierung abgeschlossen: $@$(COLOR_RESET)"

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
					@echo "$(COLOR_RED)Cleanup MiniShell.$(COLOR_RESET)"
					@rm -f $(OBJS)
					@echo "$(COLOR_RED)Cleanup Libft.$(COLOR_RESET)"
					@cd $(INCLUDE) && make clean
					@echo "$(COLOR_GREEN)Cleanup completed.$(COLOR_RESET)"

fclean:				clean
					@echo "$(COLOR_RED)Start Full-Clean.$(COLOR_RESET)"
					@rm -f $(NAME)
					@echo "$(COLOR_RED)Full-Clean Libft.$(COLOR_RESET)"
					@cd $(INCLUDE) && make fclean
					@echo "$(COLOR_GREEN)Full-Clean completed.$(COLOR_RESET)"

re:					fclean all

.PHONY:				all clean fclean re clone
