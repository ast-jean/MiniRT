###_*_*_*_*_*_*_*_*_*_*_*_*_Makefile_MiniRT_*_*_*_*_*_*_*_*_*_*_*_*_###
###-------------------------# VARIABLES ##-------------------------###
NAME 	= miniRT
BONUS 	= miniRT_bonus

SRCS_FILES 		=	miniRT.c

INCLUDE_FILES	= 	include/miniRT.h \
					include/MLX42/include/MLX42/MLX42.h \
					
LIBS =	include/libft/libft.a \
		include/MLX42/build/libmlx42.a \
		-Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
#		-I./include	\
#		-lglfw -L /Users/$(USER)/.brew/opt/glfw/lib \
#		-ldl  -pthread -lm \

MLX_FLAG		= -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib

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
CFLAGS 		= -g -Wall -Wextra -Werror 
MLXFLAGS	= -lmlx -framework OpenGL -framework AppKit
### Autres Fonctions ###
NORMINETTE 	= norminette
###------------------------## LEAK CHECK ##------------------------###
LEAK =  #working if exits
VALGRING = valgrind --track-fds=yes --track-origins=yes  --leak-check=full ./$(NAME)
###--------------------------## REGLES ##--------------------------###

mlx_glfw:
ifeq (,$(shell brew list | grep glfw))
	brew install glfw
endif
ifeq ("$(wildcard include/MLX42/build/libmlx42.a)","")
	cd include/MLX42/ && cmake -B build
	cd include/MLX42/build && make
endif

all: mlx_glfw $(NAME)

$(NAME) : $(OBJS_IN_DIR)
	@$(MAKE) -C include/libft
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
	@mkdir -p $(OBJS_DIR)
	@echo "$(BLUE)Compiling object $@ ..$(END)"
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

bonus: $(BONUS)

clean:
	@rm -f *.o
	@rm -rf $(OBJS_DIR)
	@echo "${GREEN}${BOLD}🛁 Objects Cleaned 🛁 ${END}"

fclean:	clean
	@$(MAKE) -C include/libft fclean
	@rm -rf $(NAME) $(BONUS)
#	@echo "$(GREEN)${BOLD}🚮 MLX42 build deleted 🚮${END}"
# @rm -rf include/MLX42/build
	@echo "$(GREEN)${BOLD}🚮 Exectuable deleted 🚮${END}"

leak:
	leaks --atExit -- ./$(NAME)

re: fclean all

rew: 
	@rm -rf $(NAME)
	@rm -f *.o
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s $(NAME)
	./$(NAME)

help:
	@echo "Rules: all clean fclean re"

# if glfw is not installed 
# 1. mkdir build
# 2. cd build 
# 3. cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/installation
# 4. make
