/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:37:17 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 20:24:01 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_meta_to_norm(t_lexer *lexer)
{
	lexer->curr_state = NORMAL;
	lexer->tail = new_content(lexer);
	if (lexer->tail->type == ERR)
		return (-1);
	return (0);
}

int	ft_meta_to_blank(t_lexer *lexer)
{
	lexer->curr_state = BLANK;
	lexer->tail = new_content(lexer);
	if (lexer->tail->type == ERR)
		return (-1);
	return (0);
}

int	ft_meta_to_sq(t_lexer *lexer)
{
	lexer->curr_state = SINGLE_QUOTE;
	lexer->tail = new_content(lexer);
	if (lexer->tail->type == ERR)
		return (-1);
	return (0);
}

int	ft_meta_to_dq(t_lexer *lexer)
{
	lexer->curr_state = DOUBLE_QUOTE;
	lexer->tail = new_content(lexer);
	if (lexer->tail->type == ERR)
		return (-1);
	return (0);
}

int	ft_meta_to_meta(t_lexer *lexer)
{
	char	here;
	char	next;

	here = (lexer->last_save_addr)[lexer->index - 1];
	next = (lexer->last_save_addr)[lexer->index];
	if (here != next)
	{
		lexer->tail = new_content(lexer);
		if (lexer->tail->type == ERR)
			return (-1);
		return (0);
	}
	else
		lexer->index++;
	return (0);
}
