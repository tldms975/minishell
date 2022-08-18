/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enque.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:36:57 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 18:36:59 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_enqueue_arg(t_pipe_node **pipe, char *data)
{
	t_arg_node	*new;

	new = ft_malloc(sizeof(t_arg_node));
	new->content = data;
	new->next = NULL;
	new->prev = NULL;
	if ((*pipe)->arg_list->front == NULL)
	{
		(*pipe)->arg_list->front = new;
	}
	else
	{
		new->prev = (*pipe)->arg_list->rear;
		(*pipe)->arg_list->rear->next = new;
	}
	(*pipe)->arg_list->rear = new;
	(*pipe)->arg_list->cnt += 1;
}

void	ft_enqueue_redir(t_pipe_node **pipe, t_token_type type, char *data)
{
	t_redir_node	*new;

	new = ft_malloc(sizeof(t_redir_node));
	new->file_name = data;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	if ((*pipe)->redir_list->front == NULL)
	{
		(*pipe)->redir_list->front = new;
	}
	else
	{
		new->prev = (*pipe)->redir_list->rear;
		(*pipe)->redir_list->rear->next = new;
	}
	(*pipe)->redir_list->rear = new;
	if (type == REDIR_HEREDOC)
	{
		if (data == NULL)
			ft_enqueue(&((*pipe)->lim_q), data);
		else
			ft_enqueue(&((*pipe)->lim_q), ft_strdup(data));
	}
}

int	ft_is_empty_q_pipe(t_pipe_list *queue)
{
	return (queue->cnt_pipe == 0);
}

void	ft_enqueue_pipe(t_pipe_list **queue)
{
	t_pipe_node	*new;

	new = ft_malloc(sizeof(t_pipe_node));
	new->arg_list = new_arg_list();
	new->redir_list = new_redir_list();
	new->lim_q = new_limiter_q();
	new->next = NULL;
	if ((*queue)->head == NULL)
	{
		(*queue)->head = new;
	}
	else
	{
		(*queue)->tail->next = new;
	}
	(*queue)->tail = new;
	(*queue)->cnt_pipe += 1;
}
