# 42 Rush02 Makefile

NAME		:= rush-02
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -Iincludes

SRCS		:= \
	src/utils_io.c \
	src/utils_str.c \
	src/str_extra.c \
	src/dict.c \
	src/dict_line.c \
	src/dict_read.c \
	src/num.c \
	src/convert.c \
	src/stdin_mode.c \
	src/main.c

OBJS		:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c includes/rush02.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
