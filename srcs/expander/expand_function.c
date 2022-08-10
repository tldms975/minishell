/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/07/25 20:16:48 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_save(t_buffer **buffer)
{
	char	*save;
	char	*temp;

	if ((*buffer)->save_content == NULL)
		(*buffer)->save_content = ft_substr((*buffer)->content, 0, (*buffer)->index);
	else
	{
		save = ft_substr((*buffer)->content, 0, (*buffer)->index);
		temp = (*buffer)->save_content;
		(*buffer)->save_content = ft_strjoin(temp, save);
		free(temp);
		free(save);
	}
	if (!(*buffer)->save_content)
		exit (-1);
	if (((*buffer)->content)[(*buffer)->index] != ST_NULL)
	{
		(*buffer)->content += (*buffer)->index;
		(*buffer)->index = 1;
	}
}

int	ft_ex_next_char(t_buffer *buffer)
{
	buffer->index++;
	return (0);
}

int	ft_ex_norm_to_sq(t_buffer *buffer)
{
	buffer->curr_state = EX_SI_QUO;
	new_save(&buffer);
	buffer->content += 1;
	return (0);
}

int	ft_ex_norm_to_dq(t_buffer *buffer)
{
	buffer->curr_state = EX_DO_QUO;
	new_save(&buffer);
	buffer->content += 1;
	return (0);
}

int	ft_ex_norm_to_dollar(t_buffer *buffer)
{
	buffer->curr_state = EX_DOLLAR;
	new_save(&buffer);
	return (0);
}

int	ft_blank_to_norm(t_lexer *lexer)
{
	lexer->curr_state = NORMAL;
	lexer->last_save_addr += lexer->index;
	lexer->index = 1;
	return (0);
}

int	ft_blank_to_sq(t_lexer *lexer)
{
	lexer->curr_state = SINGLE_QUOTE;
	lexer->last_save_addr += lexer->index;
	lexer->index = 1;
	return (0);
}

int	ft_blank_to_dq(t_lexer *lexer)
{
	lexer->curr_state = DOUBLE_QUOTE;
	lexer->last_save_addr += lexer->index;
	lexer->index = 1;
	return (0);
}

int	ft_blank_to_meta(t_lexer *lexer)
{
	lexer->curr_state = META;
	lexer->last_save_addr += lexer->index;
	lexer->index = 1;
	return (0);
}

int	ft_quote_to_quote(t_lexer *lexer)
{
	lexer->curr_state = NORMAL;
	lexer->index++;
	return (0);
}

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
		printf("!\n");
		if (lexer->tail->type == ERR)
			return (-1);
		return (0);
	}
	else
		lexer->index++;
	return (0);
}