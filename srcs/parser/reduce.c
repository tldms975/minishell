/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/07/25 20:16:48 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reduce_1(t_action_state **state)
{
	int				count;
	t_action_state	*temp;

	count = -1;
	while (++count < 3)
	{
		temp = (*state);
		(*state) = (*state)->prev;
		temp->prev = NULL;
		(*state)->next = NULL;
		free(temp);
	}
	(*state)->type = PIPE_LINE;
}

void	reduce_2(t_action_state **state)
{
	t_action_state	*temp;

	temp = (*state);
	(*state) = (*state)->prev;
	temp->prev = NULL;
	(*state)->next = NULL;
	free(temp);
	(*state)->type = PIPE_LINE;
}

void	reduce_3(t_action_state **state)
{
	t_action_state	*temp;

	temp = (*state);
	(*state) = (*state)->prev;
	temp->prev = NULL;
	(*state)->next = NULL;
	free(temp);
	(*state)->type = COMMAND;
}

void	reduce_4(t_action_state **state)
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
	(*state)->type = COMMAND;
}
