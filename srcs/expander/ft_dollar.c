/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:59:43 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 17:59:45 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_dollar_dq_null(t_buffer **buffer)
{
	if ((*buffer)->save_content == NULL)
			(*buffer)->save_content = ft_strdup("");
}

void	ft_dollar_non_qu(t_buffer **buffer)
{
	char			*temp;
	char			*temp1;
	t_envp_node		*temp2;

	temp = ft_substr((*buffer)->content, 0, (*buffer)->index);
	temp2 = (*buffer)->env_list->head;
	while (temp2 != NULL)
	{
		if (ft_strncmp(temp, temp2->key, ft_strlen(temp) + 1) == 0)
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
	free(temp);
	if (temp2 == NULL && (*buffer)->curr_state == EX_DO_QUO)
		ft_dollar_dq_null(buffer);
}

void	ft_dollar(t_buffer **buffer)
{
	if (*((*buffer)->content) == '?')
	{
		ft_question_mark(*buffer);
		(*buffer)->content++;
		(*buffer)->index = 0;
	}
	else
		ft_dollar_non_qu(buffer);
	ft_dollar_sub(buffer);
}
