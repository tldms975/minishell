/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_function1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:59:19 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 17:59:23 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ex_next_char(t_buffer *buffer)
{
	if (buffer->curr_state == EX_NORMAL \
		&& (buffer->content)[buffer->index] == '\\')
	{
		new_save(&buffer);
		ft_back_slash(buffer);
		return (0);
	}
	buffer->index++;
	return (0);
}

int	ft_ex_norm_to_sq(t_buffer *buffer)
{
	buffer->curr_state = EX_SI_QUO;
	new_save(&buffer);
	if (ft_check_type((buffer->content)[buffer->index]) != ST_NULL)
	{
		buffer->content += 1;
		buffer->index = 0;
	}
	return (0);
}

int	ft_ex_norm_to_dq(t_buffer *buffer)
{
	buffer->curr_state = EX_DO_QUO;
	new_save(&buffer);
	if (ft_check_type((buffer->content)[buffer->index]) != ST_NULL)
	{
		buffer->content += 1;
		buffer->index = 0;
	}
	return (0);
}

void	ft_ex_norm_to_dollar_sub(t_buffer *buffer)
{
	if (ft_check_type(*(buffer->content)) == SINGLE_QUOTE)
	{
		buffer->curr_state = EX_SI_QUO;
		buffer->content++;
		buffer->index = 0;
	}
	else if (ft_check_type(*(buffer->content)) == DOUBLE_QUOTE)
	{
		buffer->curr_state = EX_DO_QUO;
		buffer->content++;
		buffer->index = 0;
	}
	else if (*(buffer->content) == '\\')
	{
		buffer->content++;
		buffer->index = 0;
	}
	else if (buffer->curr_state != EX_NULL)
		buffer->index = 0;
}

int	ft_ex_norm_to_dollar(t_buffer *buffer)
{
	if (check_meta((buffer->content)[buffer->index + 1]) == EX_DOLLAR)
		buffer->index += 2;
	else if (ft_dollar_qoute_next_to_norm(buffer) == 1)
		;
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
			ft_ex_norm_to_dollar_sub(buffer);
		}
	}
	return (0);
}
