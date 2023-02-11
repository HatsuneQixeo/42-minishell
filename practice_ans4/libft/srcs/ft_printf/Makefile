NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# #text color
COLOR_OFF =\033[0m
RED =\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
CYAN=\033[0;36m
ORANGE=\033[38;5;214m

HEADER_DIR = $(shell find -name "includes" -type d)
HEADER = $(addprefix "-I", $(HEADER_DIR))

SRCS_DIR = srcs/
DIRS = $(shell find srcs -type d)
SRCS = $(wildcard $(foreach dir, $(DIRS), $(dir)/*.c))
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:c=o))

all : $(NAME)

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "$(YELLOW)Compiling: $<$(COLOR_OFF)\n"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADER)

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "$(GREEN)$(NAME) done!$(COLOR_OFF)\n"

bonus : all

clean :
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)removed: objs files ($(NAME))\n"

fclean : clean
	@ rm -rf $(NAME)
	@printf "$(RED)removed: $(NAME)\n"

re : fclean all

.PHONY : clean fclean re all