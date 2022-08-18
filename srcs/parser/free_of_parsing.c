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
	t_action_state	*temp;

	while (*state != NULL)
	{
		temp = *state;
		*state = (*state)->next;
		temp->prev = NULL;
		temp->next = NULL;
		ft_free((void **)&temp);
	}
}

void	ft_arg_free(t_arg_list *arg_list)
{
	void	*temp;

	while (arg_list->front != NULL)
	{
		temp = arg_list->front;
		ft_free((void **)&(arg_list->front->content));
		arg_list->front = arg_list->front->next;
		ft_free((void **)&temp);
	}
}

void	ft_redir_free(t_redir_list *redir_list)
{
	void	*temp;

	while (redir_list->front != NULL)
	{
		temp = redir_list->front;
		ft_free((void **)&(redir_list->front->file_name));
		redir_list->front = redir_list->front->next;
		ft_free((void **)&temp);
	}
}

void	ft_limq_free(t_limiter_q *lim_q)
{
	void	*temp;

	while (lim_q->front != NULL)
	{
		temp = lim_q->front;
		ft_free((void **)&(lim_q->front->data));
		lim_q->front = lim_q->front->next;
		ft_free((void **)&temp);
	}
}

void	ft_parser_free(t_pipe_list *pipe)
{
	void	*temp;

	while (pipe->head != NULL)
	{
		temp = pipe->head;
		ft_arg_free(pipe->head->arg_list);
		ft_free((void **)&(pipe->head->arg_list));
		ft_redir_free(pipe->head->redir_list);
		ft_free((void **)&(pipe->head->redir_list));
		ft_limq_free(pipe->head->lim_q);
		ft_free((void **)&(pipe->head->lim_q));
		pipe->head = pipe->head->next;
		ft_free((void **)&temp);
	}
}
