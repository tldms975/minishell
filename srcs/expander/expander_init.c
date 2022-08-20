/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:59:38 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 17:59:40 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expander_init(char *str, t_buffer **buffer, t_envp_list *list)
{
	if (buffer_init(str, buffer, list) == 1)
		;
	else if ((*buffer)->curr_state == EX_SI_QUO
		|| (*buffer)->curr_state == EX_DO_QUO)
		ft_que_init(*buffer);
}

int	buffer_init(char *str, t_buffer **buffer, t_envp_list *list)
{
	*buffer = ft_malloc(sizeof(t_buffer));
	(*buffer)->content = str;
	(*buffer)->curr_state = check_expand_type(*str);
	(*buffer)->save_content = NULL;
	(*buffer)->index = 1;
	(*buffer)->env_list = list;
	ft_back_slash(*buffer);
	if ((*buffer)->curr_state == EX_DOLLAR
		&& (check_expand_type(((*buffer)->content)[(*buffer)->index])
		== EX_NULL))
	{
		(*buffer)->curr_state = EX_NORMAL;
		return (1);
	}
	return (0);
}

void	ft_que_init_sub(t_buffer *buffer)
{
	while (check_meta_qu((buffer->content)[buffer->index]) == EX_NORMAL)
		buffer->index++;
	ft_dollar(&buffer);
	if (ft_check_type(*(buffer->content)) == DOUBLE_QUOTE)
	{
		buffer->curr_state = EX_NORMAL;
		if (ft_check_type((buffer->content)[buffer->index]) != ST_NULL)
		{
			buffer->content += 1;
			buffer->index = 0;
		}
		else if (ft_check_type((buffer->content)[buffer->index]) == ST_NULL)
			buffer->curr_state = EX_NULL;
	}
	else
		buffer->index = 0;
}

void	ft_que_init(t_buffer *buffer)
{
	buffer->content++;
	if (check_expand_type(*(buffer->content)) == EX_DOLLAR
		&& buffer->curr_state == EX_DO_QUO)
	{
		buffer->content++;
		buffer->index = 0;
		if ('0' <= *(buffer->content) && *(buffer->content) <= '9')
			buffer->content++;
		else
			ft_que_init_sub(buffer);
	}
	else
		buffer->index = 0;
}
