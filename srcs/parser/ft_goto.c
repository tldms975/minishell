/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/08/13 21:47:20 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_action_state	*new_state(void)
{
	t_action_state	*new;

	new = ft_malloc(sizeof(t_action_state));
	new->next = NULL;
	new->prev = NULL;
	new->type = NONE;
	return (new);
}

void	ft_set_type(t_token_type *type, t_action_state **state, t_token **token)
{
	if ((*token) == NULL && (*state)->type == NONE)
		*type = DOLLAR;
	else if ((*state)->type == NONE)
		*type = (*token)->type;
	else
		*type = (*state)->type;
}

void	linked_state(t_action_state **state,
		t_action_state **next, t_token **token)
{
	if ((*next)->state == STATE_STAY)
		free(*next);
	else
	{
		(*state)->next = *next;
		(*next)->prev = (*state);
		if ((*token) == NULL && (*state)->type == NONE)
			(*state)->type = DOLLAR;
		else if ((*state)->type == NONE)
		{
			(*state)->type = (*token)->type;
			(*token) = (*token)->next;
		}
		(*state) = (*next);
	}
}

int	ft_goto_sub(t_action_state **state,
		t_action_state **next, t_token_type type)
{
	if ((*state)->state == STATE_0)
		(*next)->state = ft_state_0(type);
	else if ((*state)->state == STATE_1)
		(*next)->state = ft_state_1(type);
	else if ((*state)->state == STATE_2)
		(*next)->state = ft_state_2(state, type);
	else if ((*state)->state == STATE_3)
		(*next)->state = ft_state_3(state, type);
	else if ((*state)->state == STATE_4)
		(*next)->state = ft_state_4(state, type);
	else if ((*state)->state == STATE_5)
		(*next)->state = ft_state_5(state, type);
	else
		return (1);
	return (0);
}

void	ft_goto(t_action_state **state, t_token **token)
{
	t_action_state	*next;
	t_token_type	type;

	next = new_state();
	ft_set_type(&type, state, token);
	if (ft_goto_sub(state, &next, type) == 0)
		;
	else if ((*state)->state == STATE_6)
		next->state = ft_state_6(type);
	else if ((*state)->state == STATE_7)
		next->state = ft_state_7(type);
	else if ((*state)->state == STATE_8)
		next->state = ft_state_8(state, type);
	else if ((*state)->state == STATE_9)
		next->state = ft_state_9(state, type);
	else if ((*state)->state == STATE_10)
		next->state = ft_state_10(state, type);
	linked_state(state, &next, token);
	if ((*state)->state != STATE_ERR && (*state)->state != STATE_END)
		ft_goto(state, token);
}
