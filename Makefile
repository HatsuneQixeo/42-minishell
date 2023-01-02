NAME = minishell
UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	REQUIRED_LIB = -lreadline -lncurses
endif

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MODE = none
ifeq ($(MODE), debug)
	CFLAGS += -fsanitize=address
endif

LIBFT_DIR = libft/
LIBFT_LIB = libft.a

HEADER_DIR =  includes/
SRCS_DIR = srcs/
SUBDIR = $(shell find srcs -type d)
SRCS = $(wildcard *.c $(foreach fd, $(SUBDIR), $(fd)/*.c))
NODIR_SRC = $(notdir $(SRCS))
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:c=o))

#text_color
COLOR_OFF =\033[0m
RED =\033[0;31m
GREEN =\033[0;32m
YELLOW =\033[0;33m
CYAN =\033[1;36m
MAGNETA =\033[95m 

all : $(NAME)

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(@D)
	@$(CC) -o $@  -c $< -I$(HEADER_DIR)

$(NAME) : $(OBJS)
	@make bonus -C $(LIBFT_DIR)
	@$(CC) $(SRCS) -I$(HEADER_DIR) $(REQUIRED_LIB) $(LIBFT_DIR)$(LIBFT_LIB) -o $(NAME)
	@echo "$(CYAN)$(NAME) done !$(COLOR_OFF)"

bonus : all

fclean : clean
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME) $(OBJS_DIR)
	@echo "$(RED)Removed : obj files ($(NAME))$(COLOR_OFF)"
	@echo "$(RED)Removed : $(NAME)$(COLOR_OFF)"

re : fclean all

kill :
	@killall -9 $(NAME)

.PHONY : clean fclean all re
