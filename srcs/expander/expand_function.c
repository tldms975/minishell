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
		if (!save)
			exit (-1);
		temp = (*buffer)->save_content;
		(*buffer)->save_content = ft_strjoin(temp, save);
		if (!(*buffer)->save_content)
			exit (-1);
		free(temp);
		free(save);
	}
	if (ft_check_type(((*buffer)->content)[(*buffer)->index]) != ST_NULL)
	{
		(*buffer)->content += (*buffer)->index;
		(*buffer)->index = 1;
	}
}

void	ft_dollar(t_buffer **buffer)
{
	char			*temp;
	char			*temp1;
	t_envp_node		*temp2;

	temp = ft_substr((*buffer)->content, 0, (*buffer)->index);
	temp2 = (*buffer)->env_list->head;
	while (temp2 != NULL)
	{
		if (ft_strncmp(temp, temp2->key, ft_strlen(temp)) == 0)
		{
			temp1 = (*buffer)->save_content;
			(*buffer)->save_content = ft_strjoin(temp, temp2->value);
			free(temp);
			break ;
		}
		temp2 = temp2->next;
	}
	if (ft_check_type(((*buffer)->content)[(*buffer)->index]) != ST_NULL)
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
	if (ft_check_type((buffer->content)[buffer->index]) != ST_NULL)
		buffer->content += 1;
	return (0);
}

int	ft_ex_norm_to_dq(t_buffer *buffer)
{
	buffer->curr_state = EX_DO_QUO;
	new_save(&buffer);
	if (ft_check_type((buffer->content)[buffer->index]) != ST_NULL)
		buffer->content += 1;
	return (0);
}

int	ft_ex_norm_to_dollar(t_buffer *buffer)
{
	if (check_meta((buffer->content)[buffer->index + 1]) == EX_DOLLAR)
		buffer->index += 2;
	else if (check_meta((buffer->content)[buffer->index + 1]) == EX_META)
		buffer->index++;
	else if (check_meta((buffer->content)[buffer->index + 1]) == EX_NORMAL)
	{
		new_save(&buffer);
		buffer->content += 1;
		while (check_meta((buffer->content)[buffer->index]) != EX_NORMAL)
			buffer->index++;
		ft_dollar(&buffer);
		if (ft_check_type(*(buffer->content)) == SINGLE_QUOTE)
			buffer->curr_state = EX_SI_QUO;
		else if (ft_check_type(*(buffer->content)) == DOUBLE_QUOTE)
			buffer->curr_state = EX_DO_QUO;
	}
}

int	ft_ex_qou_to_dollar(t_buffer *buffer)
{
	if (check_meta((buffer->content)[buffer->index + 1]) == EX_DOLLAR)
		buffer->index += 2;
	else if (check_meta((buffer->content)[buffer->index + 1]) == EX_META)
		buffer->index++;
	else if (check_meta((buffer->content)[buffer->index + 1]) == EX_NORMAL)
	{
		new_save(&buffer);
		buffer->content += 1;
		while (check_meta((buffer->content)[buffer->index]) != EX_NORMAL)
			buffer->index++;
		ft_dollar(&buffer);
		if (ft_check_type(*(buffer->content)) == DOUBLE_QUOTE)
		{
			buffer->curr_state = EX_NORMAL;
			if (ft_check_type((buffer->content)[buffer->index]) != ST_NULL)
				buffer->content += 1;
		}
	}
}

int	ft_ex_quo_to_quo(t_buffer *buffer)
{
	buffer->curr_state = EX_NORMAL;
	buffer->index--;
	new_save(&buffer);
	if (ft_check_type((buffer->content)[buffer->index]) != ST_NULL)
		buffer->content += 1;
	return (0);
}