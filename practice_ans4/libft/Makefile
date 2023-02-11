NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# #text color
COLOR_OFF =\033[0m
RED =\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
CYAN=\033[0;36m
ORANGE=\033[38;5;214m

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

HEADER_DIR = $(call rwildcard,srcs/,includes)
HEADER = $(addprefix "-I", $(HEADER_DIR))

SRCS_DIR = srcs/
SRCS = $(call rwildcard,srcs/,*.c)
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
	@printf "$(RED)removed: objs files ($(NAME))$(COLOR_OFF)\n"

fclean : clean
	@ rm -rf $(NAME)
	@printf "$(RED)removed: $(NAME)$(COLOR_OFF)\n"

re : fclean all

.PHONY : clean fclean re all
