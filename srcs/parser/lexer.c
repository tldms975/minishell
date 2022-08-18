/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:37:19 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 18:37:20 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_setting(t_lexer *lexer, char *input_line)
{
	lexer->index = 1;
	lexer->input_line = input_line;
	lexer->last_save_addr = input_line;
	lexer->curr_state = ft_check_type(*input_line);
	lexer->head = NULL;
	lexer->tail = NULL;
	ft_table(lexer);
}

int	ft_lexer(t_lexer *lexer)
{
	t_state		next_state;
	char		next_char;
	t_function	function;

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
