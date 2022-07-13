# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 17:14:48 by sielee            #+#    #+#              #
#    Updated: 2022/07/13 17:40:41 by sielee           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = minishell

LFT_DIR = libft
LFT_A = $(LFT_DIR)/libft.a

INC_DIR = incs
SRCS_DIR = srcs

PARSE_SRCS = $(addsuffix .c,$(addprefix parse/,\
		))
UTILS_SRCS = $(addsuffix .c,$(addprefix utils/,\
		))

SRCS =	$(addprefix $(SRCS_DIR)/,\
		main.c)\
		$(PARSE_SRCS)\
		$(UTILS_SRCS)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $^ -o $@

$(NAME): $(OBJS) $(LFT_A)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ $^

$(LFT_A) :
	@make -C $(LFT_DIR)

clean:
	rm -f $(OBJS) $(B_OBJS)
	@make clean -C $(LFT_DIR)

fclean: clean
	rm -f $(NAME) $(B_NAME)
	@make fclean -C $(LFT_DIR)

re: fclean all

.PHONY : all clean fclean re
