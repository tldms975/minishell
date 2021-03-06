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

typedef enum e_state_num
{
	STATE_0 = 0,
	STATE_1,
	STATE_2,
	STATE_3,
	STATE_4,
	STATE_5,
	STATE_6,
	STATE_7,
	STATE_8,
	STATE_9,
	STATE_10,
	STATE_END,
	STATE_ERR,
	STATE_STAY
}	t_state_num;

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
	REDIR_HEREDOC,
	ELEM,
	REDIRECTION,
	COMMAND,
	PIPE_LINE,
	DOLLAR
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

typedef struct s_redir_list
{
	char				*file_name;
	t_token_type		redir_type;
	struct s_redir_list	*next;
}	t_redir_list;

typedef struct s_arg_list
{
	char				*content;
	struct s_arg_list	*next;
}	t_arg_list;


typedef struct s_cmd
{
	t_redir_list	*redir;
	t_limiter_q		*lim_q;
	t_arg_list		*arg;
}	t_cmd;

typedef struct s_pipe_line
{
	t_cmd				*cmd;
	struct s_pipe_line	*next_pipe;
}	t_pipe_line;

typedef struct s_pipe_head
{
	t_pipe_line	*head;
	int			cnt_pipe;
}	t_pipe_head;

typedef struct s_action_state
{
	t_state_num				state;
	t_token_type			type;
	struct s_action_state	*prev;
	struct s_action_state	*next;
}	t_action_state;


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


void	reduce_1(t_action_state *state);
void	reduce_2(t_action_state *state);
void	reduce_3(t_action_state *state);
void	reduce_4(t_action_state *state);
void    reduce_5(t_action_state *state);
void	reduce_6(t_action_state *state);
void	reduce_7(t_action_state **state);


t_action_state	*new_state(void);
void	state_init(t_action_state **state, t_token **token);
void	linked_state(t_action_state **state, t_action_state **next, t_token **token);
t_state_num ft_state_0(t_action_state *state);
t_state_num ft_state_1(t_action_state *state);
t_state_num ft_state_2(t_action_state *state);
t_state_num ft_state_3(t_action_state *state);
t_state_num ft_state_4(t_action_state *state);
t_state_num ft_state_5(t_action_state *state);
t_state_num ft_state_6(t_action_state *state);
t_state_num ft_state_7(t_action_state *state);
t_state_num ft_state_8(t_action_state *state);
t_state_num ft_state_9(t_action_state *state);
t_state_num ft_state_10(t_action_state *state);
t_state_num    ft_goto(t_action_state *state, t_token *token);
int	ft_parser(t_token *token);

#endif