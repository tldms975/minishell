# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 17:14:48 by sielee            #+#    #+#              #
#    Updated: 2022/08/08 18:57:03 by sielee           ###   ########seoul.kr   #
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
					ft_goto\
					reduce\
					free_of_parsing\
					function))
UTILS_SRCS		=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/utils/,\
					basic_utils\
					exit\
					sys_utils\
					queue\
					free))
ENVP_SRCS		=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/envp/,\
					init_env\
					env_tool\
					env_vec))
TERMINAL_SRCS	=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/terminal/,\
					sig_handling))
BUILTIN_SRCS	=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/builtin/,\
					built_in\
					ft_bi_cd\
					ft_bi_echo\
					ft_bi_env\
					ft_bi_exit\
					ft_bi_export\
					ft_bi_pwd\
					ft_bi_unset))
EXECUTOR_SRCS	=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/executor/,\
					exec_process\
					exec_utils\
					exec\
					heredoc\
					redirection))
SRCS			=	$(addsuffix .c,$(addprefix $(SRCS_DIR)/,\
					main))\
					$(UTILS_SRCS)\
					$(TERMINAL_SRCS)\
					$(PARSER_SRCS)\
					$(ENVP_SRCS)\
					$(BUILTIN_SRCS)
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
