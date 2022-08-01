# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 17:14:48 by sielee            #+#    #+#              #
#    Updated: 2022/08/01 18:09:27 by sielee           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

NAME	=	minishell

INC_DIR		=	inc
SRCS_DIR	=	srcs

LFT_DIR				=	libft
LFT_LIB				=	$(LFT_DIR)/libft.a

READLINE_DIR		=	$(shell brew --prefix readline)
READLINE_INC_DIR	=	$(READLINE_DIR)/include
READLINE_LIB_DIR	=	$(READLINE_DIR)/lib
READLINE_LIB		=	$(READLINE_LIB_DIR)/libreadline.a

READLINE_FLAGS	=	-L$(READLINE_LIB_DIR) -lreadline -I$(READLINE_INC_DIR)

PARSER_SRCS		=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/parser/,\
					parse\
					lexer\
					table\
					utils_lexer\
					function))
UTILS_SRCS		=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/utils/,\
					basic_utils\
					sys_utils\
					queue\
					free))
TERMINAL_SRCS	=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/terminal/,\
					minishell\
					sig_handling))
EXECUTOR_SRCS	=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/executor/,\
					execute))
SRCS			=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/,\
					main))\
					$(UTILS_SRCS)\
					$(PARSER_SRCS)\
					$(TERMINAL_SRCS)\
#					$(EXECUTOR_SRCS)
OBJS			=	$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(READLINE_INC_DIR) -c $^ -o $@

$(NAME): $(OBJS) $(LFT_LIB) $(READLINE_LIB)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(READLINE_FLAGS) -o $@ $^

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
