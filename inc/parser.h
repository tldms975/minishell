/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:50 by sielee            #+#    #+#             */
/*   Updated: 2022/08/01 18:07:21 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_lexer		t_lexer;

typedef int		(*t_function)(t_lexer *lexer);

typedef enum e_meta
{
	LINE_EOF = 0,
	MT_TAB,
	MT_SPACE,
	MT_RIGHT,
	MT_LEFT,
	MT_PIPE,
	MT_AND,
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

typedef struct s_limiter_node
{
	struct s_limiter_node	*next;
	char					*data;
}				t_limiter_node;

typedef struct s_limiter_q
{
	struct s_limiter_node	*front;
	struct s_limiter_node	*rear;
	int						cnt;
}				t_limiter_q;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	struct s_token	*next;
}				t_token;

struct s_lexer
{
	t_state		curr_state;
	t_token		*head;
	t_token		*tail;
	t_function	function[5][5];
	char		*input_line;
	char		*last_save_addr;
	int			index;
};


t_meta	ft_check_meta(char c);
t_state	ft_check_type(char c);
t_token_type		choose_type(t_token *new);
t_token	*new_content(t_lexer *lexer);
int	ft_next_char(t_lexer *lexer);
int	ft_norm_to_blank(t_lexer *lexer);
int	ft_norm_to_sq(t_lexer *lexer);
int	ft_norm_to_dq(t_lexer *lexer);
int	ft_norm_to_meta(t_lexer *lexer);
int	ft_blank_to_norm(t_lexer *lexer);
int	ft_blank_to_sq(t_lexer *lexer);
int	ft_blank_to_dq(t_lexer *lexer);
int	ft_blank_to_meta(t_lexer *lexer);
int	ft_quote_to_quote(t_lexer *lexer);
int	ft_meta_to_norm(t_lexer *lexer);
int	ft_meta_to_blank(t_lexer *lexer);
int	ft_meta_to_sq(t_lexer *lexer);
int	ft_meta_to_dq(t_lexer *lexer);
int	ft_meta_to_meta(t_lexer *lexer);
void	lexer_setting(t_lexer *lexer, char *input_line);
int ft_lexer(t_lexer *lexer);
void	lexer_setting(t_lexer *lexer, char *input_line);
int ft_lexer(t_lexer *lexer);
void	ft_table(t_lexer *lexer);

#endif