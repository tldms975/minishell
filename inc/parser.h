/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:50 by sielee            #+#    #+#             */
/*   Updated: 2022/07/29 00:27:26 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_meta
{
	EOF = 0,
	TAB,
	SPACE,
	RIGHT,
	LEFT,
	PIPE,
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
	EOF = 0,
	ID,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_token_type;

typedef int		(*t_function)(t_lexer *lexer);

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


#endif