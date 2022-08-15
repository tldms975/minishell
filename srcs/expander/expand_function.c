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
		temp = ((*buffer)->save_content);
		save = ft_substr((*buffer)->content, 0, (*buffer)->index);
		if (!save)
			exit (-1);
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

void	ft_dollar_sub(t_buffer **buffer)
{
	if (ft_check_type(((*buffer)->content)[(*buffer)->index]) != ST_NULL)
	{
		(*buffer)->content += (*buffer)->index;
		(*buffer)->index = 1;
	}
	else if (ft_check_type(((*buffer)->content)[(*buffer)->index]) == ST_NULL)
		(*buffer)->curr_state = EX_NULL;
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
			if (temp1 == NULL)
				(*buffer)->save_content = ft_strdup(temp2->value);
			else
			{
				(*buffer)->save_content = ft_strjoin(temp1, temp2->value);
				free(temp1);
			}
			break ;
		}
		temp2 = temp2->next;
	}
	ft_dollar_sub(buffer);
	free(temp);
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
		if ('0' <= *(buffer->content) && *(buffer->content) <= '9')
		{
			buffer->content++;
			buffer->index = 0;
		}
		else
		{
			while (check_meta((buffer->content)[buffer->index]) == EX_NORMAL)
				buffer->index++;
			ft_dollar(&buffer);
			ft_ex_norm_to_dollar_sub(buffer);
		}
	}
	return (0);
}

void	ft_ex_qou_to_dollar_sub(t_buffer *buffer)
{
	while (check_meta((buffer->content)[buffer->index]) == EX_NORMAL)
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
		if ('0' <= *(buffer->content) && *(buffer->content) <= '9')
		{
			buffer->content++;
			buffer->index = 0;
		}
		else
			ft_ex_qou_to_dollar_sub(buffer);
	}
	return (0);
}

int	ft_ex_quo_to_quo(t_buffer *buffer)
{
	buffer->curr_state = EX_NORMAL;
	new_save(&buffer);
	if (ft_check_type((buffer->content)[buffer->index]) != ST_NULL)
	{
		buffer->content += 1;
		buffer->index = 0;
	}
	else if (ft_check_type((buffer->content)[buffer->index]) == ST_NULL)
		buffer->curr_state = EX_NULL;
	return (0);
}

void	ft_ex_dollar_to_sub(t_buffer *buffer)
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
	else if (check_meta(*(buffer->content)) == EX_META)
	{
		buffer->curr_state = EX_NORMAL;
		if (*(buffer->content) == '\\')
		{
			buffer->content++;
			buffer->index = 0;
		}
	}
}

int	ft_ex_dollar_to(t_buffer *buffer)
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
		{
			while (check_meta((buffer->content)[buffer->index]) == EX_NORMAL)
				buffer->index++;
			ft_dollar(&buffer);
			ft_ex_dollar_to_sub(buffer);
		}
	}
	return (0);
}