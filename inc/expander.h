/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:50 by sielee            #+#    #+#             */
/*   Updated: 2022/08/07 19:07:16 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "envp.h"

typedef struct s_buffer	t_buffer;

typedef int				(*t_fuc_exp)(t_buffer *buffer);

typedef enum e_expand_state
{
	EX_NORMAL = 0,
	EX_SI_QUO,
	EX_DO_QUO,
	EX_DOLLAR,
	EX_META,
	EX_NULL
}	t_expand_state;

typedef struct s_buffer
{
	char			*content;
	char			*save_content;
	int				index;
	t_envp_list		*env_list;
	t_expand_state	curr_state;
}	t_buffer;

typedef struct s_fuc
{
	t_fuc_exp	function[4][4];
}	t_fuc;

t_expand_state	check_expand_type(char c);
t_expand_state	check_meta(char c);
void			new_save(t_buffer **buffer);
void			ft_dollar(t_buffer **buffer);
int				ft_ex_next_char(t_buffer *buffer);
int				ft_ex_norm_to_sq(t_buffer *buffer);
int				ft_ex_norm_to_dq(t_buffer *buffer);
int				ft_ex_norm_to_dollar(t_buffer *buffer);
int				ft_ex_qou_to_dollar(t_buffer *buffer);
int				ft_ex_quo_to_quo(t_buffer *buffer);
void			ft_expander_table(t_fuc *funct);
void			ft_expander_arg(t_arg_node	**node, t_envp_list *list, \
				t_fuc funct);
void			ft_expand(t_pipe_list *pipe, t_envp_list *env);
int				ft_ex_dollar_to(t_buffer *buffer);
void			ft_question_mark(t_buffer *buffer);
void			ft_expander_init(char *str, t_buffer **buffer, \
				t_envp_list *list);
int				buffer_init(char *str, t_buffer **buffer, t_envp_list *list);
void			ft_que_init_sub(t_buffer *buffer);
void			ft_que_init(t_buffer *buffer);
t_expand_state	check_meta_qu(char c);
t_expand_state	check_expand_lim_type(char c);
void			ft_expander_arg(t_arg_node **node, t_envp_list *list, \
				t_fuc funct);
void			ft_expander_lim(t_limiter_node **node, t_fuc funct);
void			ft_expander_redir(t_redir_node **node, t_envp_list *list, \
				t_fuc funct);
void			ft_del_node_arg(t_arg_node **temp_arg, t_arg_node **front);
void			ft_del_node_redir(t_redir_node **temp_arg, \
				t_redir_node **front);
t_expand_state	check_expand_heredoc_type(char c);
void			ft_expander_heredoc(char **str, t_envp_list *list, t_fuc funct);
int				ft_ex_norm_to_dollar_heredoc(t_buffer *buffer);
int				ft_ex_dollar_to_heredoc(t_buffer *buffer);
void			ft_expander_heredoc_table(t_fuc *funct);
void			ft_back_slash(t_buffer *buffer);
int				ft_dollar_qoute_next_to_norm(t_buffer *buffer);
int				ft_dollar_to_qoute_first(t_buffer *buffer);

#endif