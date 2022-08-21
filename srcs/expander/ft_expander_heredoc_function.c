/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_heredoc_function.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:59:52 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 17:59:54 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ex_norm_to_dollar_heredoc_sub(t_buffer *buffer)
{
	if (buffer->curr_state != EX_NULL)
		buffer->index = 0;
}

int	ft_ex_norm_to_dollar_heredoc(t_buffer *buffer)
{
	if (check_meta((buffer->content)[buffer->index + 1]) == EX_DOLLAR)
		buffer->index += 2;
	else if (check_meta((buffer->content)[buffer->index + 1]) == EX_META)
		buffer->index++;
	else if (check_meta((buffer->content)[buffer->index + 1]) == EX_NORMAL)
	{
		new_save(&buffer);
		buffer->content += 1;
		buffer->index = 0;
		if ('0' <= *(buffer->content) && *(buffer->content) <= '9')
		{
			buffer->content++;
			buffer->index = 0;
		}
		else
		{
			while (check_meta_qu((buffer->content)[buffer->index]) == EX_NORMAL)
				buffer->index++;
			ft_dollar(&buffer);
			ft_ex_norm_to_dollar_heredoc_sub(buffer);
		}
	}
	return (0);
}

void	ft_ex_dollar_to_heredoc_sub(t_buffer *buffer)
{
	while (check_meta_qu((buffer->content)[buffer->index]) == EX_NORMAL)
		buffer->index++;
	ft_dollar(&buffer);
	if (check_meta_qu(*(buffer->content)) == EX_META)
		buffer->curr_state = EX_NORMAL;
	else if (check_meta_qu(*(buffer->content)) == EX_DOLLAR \
		&& check_expand_type((buffer->content)[buffer->index]) == EX_NULL)
		buffer->index = 0;
}

int	ft_ex_dollar_to_heredoc(t_buffer *buffer)
{
	if (check_meta((buffer->content)[buffer->index]) == EX_DOLLAR)
	{
		buffer->index++;
		buffer->curr_state = EX_NORMAL;
	}
	else if (check_meta((buffer->content)[buffer->index]) == EX_META)
		buffer->curr_state = EX_NORMAL;
	else if (check_meta((buffer->content)[buffer->index]) == EX_NORMAL)
	{
		buffer->content += 1;
		buffer->index = 0;
		if ('0' <= *(buffer->content) && *(buffer->content) <= '9')
		{
			buffer->content++;
			buffer->curr_state = EX_NORMAL;
		}
		else
			ft_ex_dollar_to_heredoc_sub(buffer);
	}
	return (0);
}
