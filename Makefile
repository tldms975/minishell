# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 17:14:48 by sielee            #+#    #+#              #
#    Updated: 2022/07/31 05:27:00 by sielee           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

NAME	=	minishell

INC_DIR		=	inc
SRCS_DIR	=	srcs

LFT_DIR				=	libft
LFT_LIB				=	$(LFT_DIR)/libft.a

READLINE_DIR		=	readline
READLINE_INC_DIR	=	$(READLINE_DIR)/include
READLINE_LIB_DIR	=	$(READLINE_DIR)/lib
READLINE_LIB		=	$(READLINE_LIB_DIR)/libreadline.a

READLINE_FLAGS	=	-L$(READLINE_LIB_DIR) -lreadline -I$(READLINE_INC_DIR)

PARSER_SRCS		=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/parser/,\
					parse))
UTILS_SRCS		=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/utils/,\
					basic_utils\
					sys_utils\
					queue\
					free))
EXECUTOR_SRCS	=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/executor/,\
					execute))
SRCS			=	$(addprefix $(SRCS_DIR)/,\
					main.c)\
					$(UTILS_SRCS)\
					$(PARSE_SRCS)
OBJS			=	$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(READLINE_INC_DIR)/readline -c $^ -o $@

$(NAME): $(OBJS) $(LFT_LIB) $(READLINE_LIB)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(READLINE_FLAGS) -I$(READLINE_INC_DIR) -o $@ $^

$(LFT_LIB):
	@make -C $(LFT_DIR)

clean:
	@rm -f $(OBJS)
	@make clean -C $(LFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LFT_DIR)

re: fclean all

.PHONY : all clean fclean re
