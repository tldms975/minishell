/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/07/25 20:16:48 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_(t_arg_node	**node, t_fuc funct)
{
	t_expand_state		next_state;
	char				next_char;
	t_fuc_exp			function;
	t_buffer			buffer;

	buffer.content = (*node)->content;
	buffer.curr_state = check_expand_type(*((*node)->content));
	buffer.index = 1;
	while (1)
	{
		next_char = (buffer.content)[buffer.index];
		next_state = check_expand_type(next_char);
		if (next_state == ST_NULL)
			break ;
		function = (funct.function)[buffer.curr_state][next_state];
		if (function(&buffer) == -1)
			return (-1);
	}
}

int ft_expander(t_pipe_list **pipe)
{
	t_expand_state		next_state;
	char				next_char;
	t_fuc_exp			function;
	t_buffer			buffer;

	buffer.content = (*pipe)->head->arg_list->front->content

	while (1)
	{
		next_char = (lexer->last_save_addr)[lexer->index];
		next_state = ft_check_type(next_char);
		if (next_state == ST_NULL)
			break ;
		function = (lexer->function)[lexer->curr_state][next_state];
		if (function(lexer) == -1)
			return (-1);
	}
	if (lexer->curr_state == SINGLE_QUOTE || lexer->curr_state == DOUBLE_QUOTE)
		return (-1);
	if (lexer->curr_state == META || lexer->curr_state == NORMAL)
	{
		lexer->tail = new_content(lexer);
		if (lexer->tail->type == ERR)
			return (-1);
	}
	return (0);
}