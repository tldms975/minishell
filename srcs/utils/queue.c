/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 01:51:18 by sielee            #+#    #+#             */
/*   Updated: 2022/08/18 20:01:18 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_q(t_limiter_q *queue)
{
	queue->front = NULL;
	queue->rear = NULL;
	queue->cnt = 0;
}

int	ft_is_empty_q(t_limiter_q *queue)
{
	return (queue->cnt == 0);
}

void	ft_enqueue(t_limiter_q **queue, char *data)
{
	t_limiter_node	*new;

	new = (t_limiter_node *)ft_malloc(sizeof(t_limiter_node));
	new->data = data;
	new->next = NULL;
	if (ft_is_empty_q(*queue))
	{
		(*queue)->front = new;
	}
	else
	{
		(*queue)->rear->next = new;
	}
	(*queue)->rear = new;
	(*queue)->cnt += 1;
}

void	ft_dequeue(t_limiter_q *queue)
{
	t_limiter_node	*tmp;

	if (ft_is_empty_q(queue))
		return ;
	else
	{
		tmp = queue->front;
		queue->front = tmp->next;
		ft_free((void **) &tmp->data);
		ft_free((void **) &tmp);
		queue->cnt -= 1;
	}
}
