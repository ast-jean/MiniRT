# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/21 16:04:57 by ast-jean          #+#    #+#              #
#    Updated: 2023/05/13 11:40:13 by slavoie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_atoi.c	\
	  ft_bzero.c \
	  ft_isalpha.c \
	  ft_isdigit.c \
	  ft_isalnum.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_strrchr.c \
	  ft_strchr.c \
	  ft_strlen.c \
	  ft_strlcat.c \
	  ft_strlcpy.c \
	  ft_strncmp.c \
	  ft_strnstr.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  ft_calloc.c \
	  ft_strdup.c \
	  ft_substr.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_split.c \
	  ft_itoa.c \
	  ft_strmapi.c \
	  ft_striteri.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_lstnew.c \
	  ft_lstadd_front.c \
	  ft_lstsize.c \
	  ft_lstlast.c \
	  ft_lstadd_back.c \
	  ft_lstdelone.c \
	  ft_lstclear.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_gnl.c \
	  ft_strcmp.c \

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
HEADER = -I libft

### Repertoires ###
SRCS_DIR 	= srcs/
OBJS_DIR	= objs/
INCLUDE_DIR = include/

### Colour var ###
CURSOR_UP	= \033[2A#change 0 to change number of lignes
CURSOR_DOWN	= \033[1B

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

OBJS = $(SRC:.c=.o)

SRC_IN_DIR = $(addprefix $(SRCS_DIR), $(SRC))
OBJS_IN_DIR = $(addprefix $(OBJS_DIR), $(OBJS))

###--------------------------## RULES ##--------------------------###
all: start

$(NAME) : $(OBJS_IN_DIR)
	@echo "$(BLUE)\033[1ACreating archive $(NAME)     $(END)"
	@ar -rc $(NAME) $^
	@echo "$(GREEN)${SELECTED}>Libft completed!<$(END)"
	@echo "--------------------------"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@echo "$(CURSOR_UP)Compiling $@         $(CURSOR_DOWN)"
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@
	
start:
ifeq ($(wildcard $(NAME)),)
	@echo "--------------------------"
	@echo "$(BOLD)Compiling LIBFT$(END)"
	@echo " "
	@echo " "
	@echo "--------------------------"
	@$(MAKE) $(NAME)
else
	@echo "$(NAME) already exist. try:'make re'"
endif
	
clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)Object files$(END)"

fclean: clean
	@rm -f libft.a
	@echo "$(GREEN)$(NAME) deleted$(END)"


.PHONY:
	@all bonus clean fclean re
