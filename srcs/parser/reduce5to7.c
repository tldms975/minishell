/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce5to7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:37:29 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 18:37:30 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reduce_5(t_action_state **state)
{
	int				count;
	t_action_state	*temp;

	count = -1;
	while (++count < 2)
	{
		temp = (*state);
		(*state) = (*state)->prev;
		temp->prev = NULL;
		(*state)->next = NULL;
		free(temp);
	}
	(*state)->type = REDIRECTION;
}

void	reduce_6(t_action_state **state)
{
	t_action_state	*temp;

	temp = (*state);
	(*state) = (*state)->prev;
	temp->prev = NULL;
	(*state)->next = NULL;
	free(temp);
	(*state)->type = ELEM;
}

void	reduce_7(t_action_state **state)
{
	t_action_state	*temp;

	temp = *state;
	(*state) = (*state)->prev;
	temp->prev = NULL;
	(*state)->next = NULL;
	free(temp);
	(*state)->type = ELEM;
}
