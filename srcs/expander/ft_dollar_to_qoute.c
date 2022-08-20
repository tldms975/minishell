/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_to_qoute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:18:22 by iyun              #+#    #+#             */
/*   Updated: 2022/08/20 18:18:24 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dollar_qoute_next_to_norm(t_buffer *buffer)
{
	if (check_expand_type((buffer->content)[buffer->index + 1]) \
			== EX_DO_QUO || \
			check_expand_type((buffer->content)[buffer->index + 1]) \
			== EX_SI_QUO)
	{
		new_save(&buffer);
		buffer->content += 1;
		buffer->index = 0;
		if (check_expand_type((buffer->content)[buffer->index]) == EX_DO_QUO)
			buffer->curr_state = EX_DO_QUO;
		else if (check_expand_type((buffer->content)[buffer->index]) \
				== EX_SI_QUO)
			buffer->curr_state = EX_SI_QUO;
		buffer->content += 1;
		return (1);
	}
	return (0);
}

int	ft_dollar_to_qoute_first(t_buffer *buffer)
{
	if (check_expand_type((buffer->content)[buffer->index]) \
			== EX_DO_QUO || \
			check_expand_type((buffer->content)[buffer->index]) == EX_SI_QUO)
	{
		buffer->content += 1;
		buffer->index = 0;
		if (check_expand_type((buffer->content)[buffer->index]) == EX_DO_QUO)
			buffer->curr_state = EX_DO_QUO;
		else if (check_expand_type((buffer->content)[buffer->index]) \
				== EX_SI_QUO)
			buffer->curr_state = EX_SI_QUO;
		buffer->content += 1;
		return (1);
	}
	return (0);
}
