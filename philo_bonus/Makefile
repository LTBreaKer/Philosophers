NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

SR_PATH = ./src/

OB_PATH = ./obj/

INCLUDE = -I ./includes

SR =	philo_bonus.c				\
			philo_bonus_utils.c	\
			

SRCS = $(addprefix ${SR_PATH}, ${SR})

OBJS = $(addprefix ${OB_PATH}, ${SR:.c=.o})

all	:	${NAME}

${OB_PATH}%.o	:	${SR_PATH}%.c
			@mkdir -p ${OB_PATH}
			cc ${CFLAGS} -c $< -o $@

${NAME}	:	${OBJS}
	cc ${CFLAGS} ${INCLUDE} -o ${NAME} ${OBJS}

clean:
			${RM} ${OBJS}
			${RM} -r ${OB_PATH}

fclean: clean
			${RM} ${NAME}

re:	fclean all

.PHONY: clean fclean re