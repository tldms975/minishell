/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_lim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:59:55 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 17:59:56 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exp_lim_init(t_buffer **buffer, t_limiter_node **node)
{
	*buffer = ft_malloc(sizeof(t_buffer));
	(*buffer)->content = (*node)->data;
	(*buffer)->save_content = NULL;
	(*buffer)->curr_state = check_expand_lim_type(*((*node)->data));
	(*buffer)->index = 1;
	if ((*buffer)->curr_state != EX_SI_QUO
		&& (*buffer)->curr_state != EX_DO_QUO)
		(*node)->state = QOUTE_OFF;
	else
	{
		(*buffer)->content++;
		(*buffer)->index = 0;
		(*node)->state = QOUTE_ON;
	}
}

void	ft_expander_lim(t_limiter_node **node, t_fuc funct)
{
	t_expand_state		next_state;
	char				next_char;
	t_fuc_exp			function;
	t_buffer			*buffer;

	ft_exp_lim_init(&buffer, node);
	while (1)
	{
		next_char = (buffer->content)[buffer->index];
		next_state = check_expand_lim_type(next_char);
		if ((next_state == EX_SI_QUO || next_state == EX_DO_QUO)
			&& (*node)->state == QOUTE_OFF)
			(*node)->state = QOUTE_ON;
		if (next_state == EX_NULL)
			break ;
		function = (funct.function)[buffer->curr_state][next_state];
		if (function(buffer) == -1)
			return ;
	}
	if (buffer->curr_state == EX_NORMAL)
		new_save(&buffer);
	ft_free((void **)(&(*node)->data));
	(*node)->data = buffer->save_content;
	free(buffer);
}
