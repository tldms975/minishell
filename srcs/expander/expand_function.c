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

void	ft_question_mark(t_buffer *buffer)
{
	char	*temp;
	char	*temp2;

	temp = buffer->save_content;
	temp2 = ft_itoa();
	if (temp == NULL)
		buffer->save_content = ft_strdup(temp2);
	else
	{
		buffer->save_content = ft_strjoin(temp, temp2);
		free(temp);
	}
	free(temp2);
	buffer->content++;
	buffer->index = 0;
}