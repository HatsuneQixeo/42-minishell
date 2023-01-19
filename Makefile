NAME = minishell
UNAME = $(shell uname)

#text_color
DEFAULT		:=	\033[0m
RED			:=	\033[0;31m
GREEN		:=	\033[0;32m
YELLOW		:=	\033[0;33m
CYAN		:=	\033[1;36m
MAGENTA 	:=	\033[95m

EXTRA_LIBS	:=	-lreadline -lncurses


CC			:=	gcc
# CFLAGS		:=	-Wall -Wextra -Werror
CFLAGS		:=	-Wall -Werror
# CFLAGS		+=	-fsanitize=address -g3
LIBFT_DIR	:=	libft/
LIBFT		:=	${LIBFT_DIR}libft.a
LIBFT_INCLUDE	:=	${LIBFT_DIR}include/
LIBFT_MAKE	:=	make -C ${LIBFT_DIR}

HEADER_DIR	:=	includes/
HEADER		:=	$(wildcard ${INCLUDE}*)

SRC_DIR		:=	srcs
DIRS 		:=	$(shell find ${SRC_DIR} -type d)
SRCS		:=	$(wildcard $(foreach fd, $(DIRS), $(fd)/*.c))
OBJS_DIR	:=	objs/
OBJS		:=	$(addprefix $(OBJS_DIR), $(SRCS:c=o))

all : ${NAME}

${OBJS_DIR} :
	mkdir $@

$(OBJS_DIR)%.o : %.c $(HEADER)
	@mkdir -p $(@D)
	@# printf "$(MAGENTA)Compiling: $<$(DEFAULT)\n"
	@$(CC) ${CFLAGS} -I${HEADER_DIR} -I${LIBFT_INCLUDE} -c $< -o $@

$(NAME) : $(OBJS)
	@${LIBFT_MAKE}
	$(CC) ${CFLAGS} $(OBJS) -I${HEADER_DIR} $(LIBFT) $(EXTRA_LIBS) -o $(NAME)
	@#echo "$(CYAN)$(NAME) done !$(DEFAULT)"

san :
	$(CC) ${CFLAGS} $(SRCS) -I${HEADER_DIR} -I${LIBFT_INCLUDE} $(LIBFT) $(EXTRA_LIBS) -o $(NAME) -fsanitize=address -g3

fclean :
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR) $(NAME)
	@echo "$(RED)Removed : obj files ($(NAME))$(DEFAULT)"
	@echo "$(RED)Removed : $(NAME)$(DEFAULT)"

re : fclean ${OBJS_DIR} all

kill :
	@killall -9 $(NAME)

valgrind :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY : clean fclean all re
