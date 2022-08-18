/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_q_and_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:37:21 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 18:37:22 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_limiter_q	*new_limiter_q(void)
{
	t_limiter_q	*new;

	new = ft_malloc(sizeof(t_limiter_q));
	new->front = NULL;
	new->rear = NULL;
	new->cnt = 0;
	return (new);
}

t_redir_list	*new_redir_list(void)
{
	t_redir_list	*new;

	new = ft_malloc(sizeof(t_redir_list));
	new->front = NULL;
	new->rear = NULL;
	return (new);
}

t_arg_list	*new_arg_list(void)
{
	t_arg_list	*new;

	new = ft_malloc(sizeof(t_arg_list));
	new->front = NULL;
	new->rear = NULL;
	new->cnt = 0;
	return (new);
}
