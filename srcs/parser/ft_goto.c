/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/07/25 20:16:48 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_action_state	*new_state(t_action_state *state, t_token *token)
{
	t_action_state	*new;

	new = ft_malloc(sizeof(t_action_state));
	new->next = NULL;
	new->prev = state;
	if (token == NULL)
		new->type = DOLLAR;
	else
		new->type = token->type;
	state = new;
	return (new);
}

t_state_num ft_state_0(t_action_state *state)
{
	if (state->type == REDIR_APPEND || state->type == REDIR_HEREDOC
		|| state->type == REDIR_IN || state->type == REDIR_OUT)
		return (STATE_6);
	else if (state->type == ID)
		return (STATE_5);
	else if (state->type == PIPE_LINE)
		return (STATE_1);
	else if (state->type == COMMAND)
		return (STATE_2);
	else if (state->type == REDIRECTION)
		return (STATE_4);
	else if (state->type == ELEM)
		return (STATE_3);
	return (STATE_ERR);
}

t_state_num ft_state_1(t_action_state *state)
{
	if (state->type == DOLLAR)
		return (STATE_END);
	return (STATE_ERR);
}

t_state_num ft_state_2(t_action_state *state)
{
	if (state->type == PIPE)
		return (STATE_7);
	else if (state->type == REDIR_APPEND || state->type == REDIR_HEREDOC
		|| state->type == REDIR_IN || state->type == REDIR_OUT)
		return (STATE_6);
	else if (state->type == ID)
		return (STATE_5);
	else if (state->type == REDIRECTION)
		return (STATE_4);
	else if (state->type == ELEM)
		return (STATE_8);
	else if (state->type == DOLLAR)
	{
		reduce_2(state);
		return (state->state);
	}
	return (STATE_ERR);
}

t_state_num ft_state_3(t_action_state *state)
{
	if (state->type == REDIR_APPEND || state->type == REDIR_HEREDOC
		|| state->type == REDIR_IN || state->type == REDIR_OUT
		|| state->type == PIPE || state->type == ID
		|| state->type == DOLLAR)
	{
		reduce_3(state);
		return (state->state);
	}
	return (STATE_ERR);
}

t_state_num ft_state_4(t_action_state *state)
{
	if (state->type == REDIR_APPEND || state->type == REDIR_HEREDOC
		|| state->type == REDIR_IN || state->type == REDIR_OUT
		|| state->type == PIPE || state->type == ID
		|| state->type == DOLLAR)
	{
		reduce_6(state);
		return (state->state);
	}
	return (STATE_ERR);
}

t_state_num ft_state_5(t_action_state *state)
{
	if (state->type == REDIR_APPEND || state->type == REDIR_HEREDOC
		|| state->type == REDIR_IN || state->type == REDIR_OUT
		|| state->type == PIPE || state->type == ID
		|| state->type == DOLLAR)
	{
		reduce_7(state);
		return (state->state);
	}
	return (STATE_ERR);
}

t_state_num ft_state_6(t_action_state *state)
{
	if (state->type == ID)
		return (STATE_9);
	return (STATE_ERR);
}

t_state_num ft_state_7(t_action_state *state)
{
	if (state->type == REDIR_APPEND || state->type == REDIR_HEREDOC
		|| state->type == REDIR_IN || state->type == REDIR_OUT)
		return (STATE_6);
	else if (state->type == ID)
		return (STATE_5);
	else if (state->type == PIPE_LINE)
		return (STATE_10);
	else if (state->type == COMMAND)
		return (STATE_2);
	else if (state->type == REDIRECTION)
		return (STATE_4);
	else if (state->type == ELEM)
		return (STATE_3);
	return (STATE_ERR);
}

t_state_num ft_state_8(t_action_state *state)
{
	if (state->type == REDIR_APPEND || state->type == REDIR_HEREDOC
		|| state->type == REDIR_IN || state->type == REDIR_OUT
		|| state->type == PIPE || state->type == ID
		|| state->type == DOLLAR)
	{
		reduce_4(state);
		return (state->state);
	}
	return (STATE_ERR);
}

t_state_num ft_state_9(t_action_state *state)
{
	if (state->type == REDIR_APPEND || state->type == REDIR_HEREDOC
		|| state->type == REDIR_IN || state->type == REDIR_OUT
		|| state->type == PIPE || state->type == ID
		|| state->type == DOLLAR)
	{
		reduce_5(state);
		return (state->state);
	}
	return (STATE_ERR);
}

t_state_num ft_state_10(t_action_state *state)
{
	if (state->type == DOLLAR)
	{
		reduce_1(state);
		return (state->state);
	}
	return (STATE_ERR);
}

void    ft_goto(t_action_state *state, t_token *token)
{
	new_state(state, token);
	token = token->next;
	if (state->state = STATE_0)
		state->state = ft_state_0(state);
	else if (state->state) = 
}