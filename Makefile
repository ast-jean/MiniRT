###_*_*_*_*_*_*_*_*_*_*_*_*_Makefile_MiniRT_*_*_*_*_*_*_*_*_*_*_*_*_###
###-------------------------# VARIABLES ##-------------------------###
NAME 	= miniRT
BONUS 	= miniRT_bonus

UNAME :=$(shell uname)
ARCH  :=$(shell uname -m)

SRCS_FILES 		=	miniRT.c \
					rayTracing/rayTracing.c \
					rayTracing/check.c \
					rayTracing/colors.c \
					rayTracing/shading.c \
					parsing/parsing.c \
					parsing/objects.c \
					parsing/colors.c \
					parsing/converter.c \
					parsing/scene.c \
					parsing/debug.c \
					parsing/utils.c \
					math/Fixed.c \
					math/vectors/Vectors.c \
					math/vectors/ray.c \
					math/vectors/Vectors_ops.c \
					math/math_other.c

INCLUDE_FILES	= 	miniRT.h \
					objects.h \
					Vectors.h \
					MLX42/include/MLX42/MLX42.h
LIBS = include/libft/libft.a \
		include/libft_dlist/dlist.a \
		include/MLX42/build/libmlx42.a

ifeq ($(UNAME), Darwin)
LIBS += -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
else ifeq ($(UNAME), Linux)
LIBS +=	-Iinclude -lglfw -lm -ldl -pthread
ifeq (,$(shell pkg-config --exists glfw3 && echo "found"))
$(error GLFW not found. Please install it via your package manager. For example, on Ubuntu or Debian-based systems: sudo apt-get install libglfw3-dev)
endif
else
$(error Unsupported OS : $(UNAME))
endif
### Repertoires ###
SRCS_DIR 	= srcs/
OBJS_DIR	= objs/
INCLUDE_DIR = include/

## Naming files ##
SRCS 		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
INCLUDE 	= $(addprefix $(INCLUDE_DIR), $(INCLUDE_FILES))
OBJS 		= $(SRCS_FILES:.c=.o)
OBJS_IN_DIR	= $(addprefix $(OBJS_DIR), $(OBJS))


### Colour var ###
CLEAR_LINE	= \033[2K
CURSOR_UP	= \033[0A #change 0 to change number of lignes
CURSOR_DOWN	= \033[0B

END			= \033[0m
BOLD		= \033[1m
ITALIC		= \033[3m
URL			= \033[4m
BLINK		= \033[5m
BLINK2		= \033[6m
SELECTED	= \033[7m

BLACK		= \033[30m
RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
VIOLET		= \033[35m
CYAN		= \033[36m
WHITE		= \033[37m

### Compilations et archivage ###
CC 			= gcc
CFLAGS 		= -Wall -Wextra -g -Wno-error=misleading-indentation

###--------------------------## REGLES ##--------------------------###
all: mlx_glfw $(NAME)

mlx_glfw:
	@echo " "
ifeq ("$(wildcard include/MLX42/build/libmlx42.a)","")
	cd include/MLX42/ && cmake -B build
	cd include/MLX42/build && make
endif


$(NAME) : $(INCLUDE) $(OBJS_IN_DIR)
	@$(MAKE) -C include/libft
	@$(MAKE) -C include/libft_dlist
	@echo "$(CLEAR_LINE)$(BLUE)Compiling $(NAME)...$(END)"
	@$(CC) $(CFLAGS) $(OBJS_IN_DIR) $(LIBS) $(MLXFLAGS) -o $(NAME)
	@echo "$(CLEAR_LINE)${GREEN}${BOLD}Compilation done:${END}\n"

$(BONUS): $(OBJS)
	@echo "$(BLUE)Compiling $(BONUS)...$(END)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(OBJS_IN_DIR) $(LIBS) $(MLXFLAGS) -o $(BONUS)
	@mv -f *.o $(OBJS_DIR)
	@echo "${GREEN}${BOLD}Compilation done:${END}\n"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)parsing $(OBJS_DIR)rayTracing $(OBJS_DIR)math/vectors 
	@echo "$(BLUE)Compiling object $@ ..$(END)"
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

bonus: $(BONUS)

clean:
	@rm -f *.o
	@rm -rf $(OBJS_DIR)
	@echo "${GREEN}${BOLD}🛁 Objects Cleaned 🛁 ${END}"

fclean:	clean
	@$(MAKE) -C include/libft fclean
	@$(MAKE) -C include/libft_dlist fclean
	@rm -rf $(NAME) $(BONUS)
	@echo "$(GREEN)${BOLD}🚮 Exectuable deleted 🚮${END}"

leak:
	leaks -list -fullContent --atExit -- ./$(NAME) test.rt

valgrind:
	valgrind --leak-check=full --suppressions=supp.txt  --show-leak-kinds=reachable -- ./$(NAME) test.rt
#	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
re: fclean all

rew: 
	@rm -rf $(NAME)
	@rm -f *.o
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s $(NAME)

help:
	@echo "Rules: all clean fclean re"
