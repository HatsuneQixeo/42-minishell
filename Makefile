NAME		:=	minishell
EXTRA_LIBS	:=	-lreadline -lncurses
UNUSED_SET	:=	-Wno-unused-parameter -Wno-unused-function -Wno-unused-variable
CC			:=	gcc
# CFLAGS		:=	-Wall -Wextra -Werror
CFLAGS		:=	-Wall -Werror -g3
CFLAGS		+=	${UNUSED_SET}
# CFLAGS		+=	-fsanitize=address
LIBFT_DIR	:=	libft/
LIBFT		:=	${LIBFT_DIR}libft.a
LIBFT_INCLUDE	:=	${LIBFT_DIR}include/
LIBFT_MAKE	:=	make -C ${LIBFT_DIR}

HEADER_DIR	:=	include/
HEADER		:=	$(wildcard ${INCLUDE}*)

SRC_DIR		:=	srcs
DIRS 		:=	$(shell find ${SRC_DIR} -type d)
SRCS		:=	$(wildcard $(foreach fd, $(DIRS), $(fd)/*.c))
OBJS_DIR	:=	objs/
OBJS		:=	$(addprefix ${OBJS_DIR}, $(SRCS:c=o))
RM			:=	rm -rf
#text_color
DEFAULT		:=	\033[0m
RED			:=	\033[0;31m
GREEN		:=	\033[0;32m
YELLOW		:=	\033[0;33m
CYAN		:=	\033[1;36m
MAGENTA 	:=	\033[95m

all : ${OBJS_DIR} ${NAME}

${OBJS_DIR} :
	mkdir $@

${OBJS_DIR}%.o : %.c ${HEADER}
	@mkdir -p ${@D}
	@# printf "${MAGENTA}Compiling: $<${DEFAULT}\n"
	${CC} ${CFLAGS} -I${HEADER_DIR} -I${LIBFT_INCLUDE} -c $< -o $@

${NAME} : ${OBJS}
	@${LIBFT_MAKE} && ${CC} ${CFLAGS} -I${HEADER_DIR} $^ ${LIBFT} ${EXTRA_LIBS} -o $@ && echo "$(CYAN)${NAME} done !$(DEFAULT)"

san : ${SRCS}
	@${LIBFT_MAKE} && \
	${CC} ${CFLAGS} -fsanitize=address -I${HEADER_DIR} -I${LIBFT_INCLUDE} $^ ${LIBFT} ${EXTRA_LIBS} -o ${NAME}

clean:
	@${LIBFT_MAKE} clean
	${RM} ${OBJS_DIR}

fclean: clean
	@${LIBFT_MAKE} fclean
	${RM} ${NAME}

re : fclean all

kill :
	@killall -9 ${NAME}

valgrind :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME}

.PHONY : clean fclean all re
