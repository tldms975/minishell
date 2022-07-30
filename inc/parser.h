/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:50 by sielee            #+#    #+#             */
/*   Updated: 2022/07/30 18:46:58 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_meta
{
	EOF = 0,
	MT_TAB,
	MT_SPACE,
	MT_RIGHT,
	MT_LEFT,
	MT_PIPE,
	NON_META
}	t_meta;

typedef enum e_state
{
	NORMAL = 0,
	BLANK,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	META,
	ST_NULL
}	t_state;

typedef enum e_token_type
{
	ERR = 0,
	ID,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_token_type;


typedef struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_lexer
{
	t_state		curr_state;
	t_token		*head;
	t_token		*tail;
	t_function	function[5][5];
	char		*input_line;
	char		*last_save_addr;
	int			index;
}				t_lexer;

typedef int		(*t_function)(t_lexer *lexer);

t_meta	ft_check_meta(char c);
t_state	ft_check_type(char c);

#endif