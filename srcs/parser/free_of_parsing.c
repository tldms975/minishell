/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_of_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/07/25 20:16:48 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_state_free(t_action_state **state)
{
	t_action_state *temp;

	while (*state != NULL)
	{
		temp = *state;
		*state = (*state)->next;
		temp->prev = NULL;
		temp->next = NULL;
		ft_free((void **)&temp);
	}
}

void	ft_parser_free(t_pipe_list *pipe)
{
	void	*temp;

	while (pipe->head != NULL)
	{
		while (pipe->head->arg_list->front != NULL)
		{
			temp = pipe->head->arg_list->front;
			ft_free((void **)&(pipe->head->arg_list->front->content));
			pipe->head->arg_list->front = pipe->head->arg_list->front->next;
			ft_free((void **)&temp);
		}
		ft_free((void **)&(pipe->head->arg_list));
		while (pipe->head->redir_list->front != NULL)
		{
			temp = pipe->head->redir_list->front;
			ft_free((void **)&(pipe->head->redir_list->front->file_name));
			pipe->head->redir_list->front = pipe->head->redir_list->front->next;
			ft_free((void **)&temp);
		}
		ft_free((void **)&(pipe->head->redir_list));
		while (pipe->head->lim_q->front != NULL)
		{
			temp = pipe->head->lim_q->front;
			ft_free((void **)&(pipe->head->lim_q->front->data));
			pipe->head->lim_q->front = pipe->head->lim_q->front->next;
			ft_free((void **)&temp);
		}
		ft_free((void **)&(pipe->head->lim_q));
		pipe->head = pipe->head->next;
	}
}