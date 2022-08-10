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
    EX_NULL
}	t_expand_state;

typedef struct s_buffer
{
	char			*content;
	char			*save_content;
	int				index;
	t_expand_state	curr_state;
}	t_buffer;

typedef struct s_fuc
{
	t_fuc_exp	function[4][4];
}	t_fuc;

t_expand_state	check_expand_type(char c);

#endif