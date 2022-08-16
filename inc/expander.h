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

typedef int		(*t_fuc_exp)(t_buffer *buffer);

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
t_expand_state check_meta(char c);
void	new_save(t_buffer **buffer);
void	ft_dollar(t_buffer **buffer);
int	ft_ex_next_char(t_buffer *buffer);
int	ft_ex_norm_to_sq(t_buffer *buffer);
int	ft_ex_norm_to_dq(t_buffer *buffer);
int	ft_ex_norm_to_dollar(t_buffer *buffer);
int	ft_ex_qou_to_dollar(t_buffer *buffer);
int	ft_ex_quo_to_quo(t_buffer *buffer);
void	ft_expander_table(t_fuc *funct);
void	ft_expander_arg(t_arg_node	**node, t_envp_list *list, t_fuc funct);
void	ft_expand(t_pipe_list *pipe, t_envp_list *env);
int	ft_ex_dollar_to(t_buffer *buffer);
void	ft_question_mark(t_buffer *buffer);

#endif