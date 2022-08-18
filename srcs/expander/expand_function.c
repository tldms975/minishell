/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/08/17 17:22:27 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	new_save(t_buffer **buffer)
{
	char	*save;
	char	*temp;

	if ((*buffer)->save_content == NULL)
		(*buffer)->save_content = ft_substr((*buffer)->content,
				0, (*buffer)->index);
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

void	ft_question_mark(t_buffer *buffer)
{
	char	*temp;
	char	*temp2;

	temp = buffer->save_content;
	temp2 = ft_itoa(g_exit_status);
	if (temp == NULL)
		buffer->save_content = ft_strdup(temp2);
	else
	{
		buffer->save_content = ft_strjoin(temp, temp2);
		free(temp);
	}
	free(temp2);
}
