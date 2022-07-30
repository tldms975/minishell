# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 17:14:48 by sielee            #+#    #+#              #
#    Updated: 2022/07/30 22:21:36 by sielee           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

NAME = minishell

INC_DIR = inc
SRCS_DIR = srcs

LFT_DIR				=	libft
LFT_LIB				=	$(LFT_DIR)/libft.a
READLINE_DIR		=	readline
READLINE_LIB		=	$(READLINE_DIR)/libreadline.a
READLINE_INC_DIR	=	$(READLINE_DIR)/include
READLINE_LIB_DIR	=	$(READLINE_DIR)/lib

PARSER_SRCS = $(addsuffix .c,$(addprefix parser/,\
		parse))
UTILS_SRCS = $(addsuffix .c,$(addprefix utils/,\
		basic_utils\
		sys_utils\
		queue\
		free))
EXECUTOR_SRCS = $(addsuffix .c,$(addprefix executor/,\
		execute))
SRCS =	$(addprefix $(SRCS_DIR)/,\
		main.c)\
		$(PARSE_SRCS)\
		$(UTILS_SRCS)

OBJS = $(SRCS:.c=.o)

READLINE_FLAGS = -L$(READLINE_LIB_DIR) -lreadline -I$(READLINE_INC_DIR)

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $^ -o $@

$(NAME): $(OBJS) $(LFT_LIB)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(READLINE_FLAGS) -o $@ $^

$(LFT_LIB) :
	@make -C $(LFT_DIR)

clean:
	rm -f $(OBJS) $(B_OBJS)
	@make clean -C $(READLINE_DIR)
	@make clean -C $(LFT_DIR)

fclean: clean
	rm -f $(NAME) $(B_NAME)
	@make fclean -C $(READLINE_DIR)
	@make fclean -C $(LFT_DIR)

re: fclean all

.PHONY : all clean fclean re
