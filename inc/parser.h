/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:50 by sielee            #+#    #+#             */
/*   Updated: 2022/08/19 16:20:16 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "envp.h"

typedef struct s_lexer		t_lexer;

typedef int					(*t_function)(t_lexer *lexer);

typedef enum e_qoute_state
{
	QOUTE_ON = 0,
	QOUTE_OFF
}	t_qoute_state;

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
	DOLLAR,
	NONE
}	t_token_type;

typedef struct s_limiter_node
{
	struct s_limiter_node	*next;
	char					*data;
	t_qoute_state			state;
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
	struct s_redir_node	*front;
	struct s_redir_node	*rear;
}	t_redir_list;

typedef struct s_redir_node
{
	char				*file_name;
	t_token_type		type;
	struct s_redir_node	*next;
	struct s_redir_node	*prev;
}	t_redir_node;

typedef struct s_arg_list
{
	struct s_arg_node	*front;
	struct s_arg_node	*rear;
	int					cnt;
}	t_arg_list;

typedef struct s_arg_node
{
	char				*content;
	struct s_arg_node	*next;
	struct s_arg_node	*prev;
}	t_arg_node;

typedef struct s_pipe_node
{
	t_redir_list		*redir_list;
	t_limiter_q			*lim_q;
	t_arg_list			*arg_list;
	t_envp_list			*env_list;
	struct s_pipe_node	*next;
}				t_pipe_node;

typedef struct s_pipe_list
{
	t_pipe_node	*head;
	t_pipe_node	*tail;
	int			cnt_pipe;
	int			is_heredoc;
}	t_pipe_list;

typedef struct s_action_state
{
	t_state_num				state;
	t_token_type			type;
	struct s_action_state	*prev;
	struct s_action_state	*next;
}	t_action_state;

t_meta			ft_check_meta(char c);
t_state			ft_check_type(char c);
t_token_type	choose_type(t_token *new);
t_token			*new_content(t_lexer *lexer);
int				ft_next_char(t_lexer *lexer);
int				ft_norm_to_blank(t_lexer *lexer);
int				ft_norm_to_sq(t_lexer *lexer);
int				ft_norm_to_dq(t_lexer *lexer);
int				ft_norm_to_meta(t_lexer *lexer);
int				ft_blank_to_norm(t_lexer *lexer);
int				ft_blank_to_sq(t_lexer *lexer);
int				ft_blank_to_dq(t_lexer *lexer);
int				ft_blank_to_meta(t_lexer *lexer);
int				ft_quote_to_quote(t_lexer *lexer);
int				ft_meta_to_norm(t_lexer *lexer);
int				ft_meta_to_blank(t_lexer *lexer);
int				ft_meta_to_sq(t_lexer *lexer);
int				ft_meta_to_dq(t_lexer *lexer);
int				ft_meta_to_meta(t_lexer *lexer);
void			lexer_setting(t_lexer *lexer, char *input_line);
int				ft_lexer(t_lexer *lexer);
void			lexer_setting(t_lexer *lexer, char *input_line);
int				ft_lexer(t_lexer *lexer);
void			ft_table(t_lexer *lexer);
void			reduce_1(t_action_state **state);
void			reduce_2(t_action_state **state);
void			reduce_3(t_action_state **state);
void			reduce_4(t_action_state **state);
void			reduce_5(t_action_state **state);
void			reduce_6(t_action_state **state);
void			reduce_7(t_action_state **state);
t_action_state	*new_state(void);
void			linked_state(t_action_state **state, t_action_state **next, \
				t_token **token);
t_state_num		ft_state_0(t_token_type type);
t_state_num		ft_state_1(t_token_type type);
t_state_num		ft_state_2(t_action_state **state, t_token_type type);
t_state_num		ft_state_3(t_action_state **state, t_token_type type);
t_state_num		ft_state_4(t_action_state **state, t_token_type type);
t_state_num		ft_state_5(t_action_state **state, t_token_type type);
t_state_num		ft_state_6(t_token_type type);
t_state_num		ft_state_7(t_token_type type);
t_state_num		ft_state_8(t_action_state **state, t_token_type type);
t_state_num		ft_state_9(t_action_state **state, t_token_type type);
t_state_num		ft_state_10(t_action_state **state, t_token_type type);
void			ft_goto(t_action_state **state, t_token **token);
int				ft_parser(t_pipe_list *pipe_head, t_token *token, \
				t_envp_list *env);
void			ft_set_type(t_token_type *type, t_action_state **state, \
				t_token **token);
void			ft_enqueue_arg(t_pipe_node **pipe, char *data);
void			ft_enqueue_redir(t_pipe_node **pipe, t_token_type type, \
				char *data);
int				ft_is_empty_q_pipe(t_pipe_list *queue);
void			ft_enqueue_pipe(t_pipe_list **queue);
t_limiter_q		*new_limiter_q(void);
t_redir_list	*new_redir_list(void);
t_arg_list		*new_arg_list(void);
void			ft_arg_id(t_pipe_node **pipe, t_token **token);
int				ft_arg_redir_in(t_pipe_node **pipe, t_token **token);
int				ft_arg_redir_out(t_pipe_node **pipe, t_token **token);
int				ft_arg_redir_append(t_pipe_node **pipe, t_token **token);
int				ft_arg_heredoc(t_pipe_node **pipe, t_token **token);
int				ft_arg_pipe(t_token **token);
void			ft_token_free(t_lexer *lexer);
void			ft_state_free(t_action_state **state);
void			ft_parser_free(t_pipe_list *pipe);

#endif