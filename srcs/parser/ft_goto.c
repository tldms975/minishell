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

t_action_state	*new_state(void)
{
	t_action_state	*new;

	new = ft_malloc(sizeof(t_action_state));
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	state_init(t_action_state **state, t_token **token)
{
	t_action_state	*new;

	new = new_state();
	new->state = STATE_0;
	if (token == NULL)
		new->type = DOLLAR;
	else
	{
		new->type = (*token)->type;
		(*token) = (*token)->next; // 토큰 프리하기!
	}
	*state = new;
}

void	linked_state(t_action_state **state, t_action_state **next, t_token **token)
{
	if ((*next)->state == STATE_STAY)
		free(*next);
	else
	{
		(*state)->next = *next;
		(*next)->prev = (*state);
		if ((*token) == NULL)
			(*next)->type = DOLLAR;
		else
		{
			(*next)->type = (*token)->type;
			(*token) = (*token)->next; // 토큰 프리하기!
		}
		(*state) = (*next);
	}
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
		reduce_7(&state);
		printf("type : %d in st_5\n", (state)->type);
		// printf("state : %d in st_5\n", state->state);
		// printf("type : %d in st_5\n", state->type);
		return (STATE_STAY);
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

t_state_num    ft_goto(t_action_state *state, t_token *token)
{
	t_action_state	*next;

	next = new_state();
	printf("state : %d in first\n", state->state);
	printf("type : %d in first\n", state->type);
	if (state->state == STATE_0)
		next->state = ft_state_0(state);
	else if (state->state == STATE_1)
		next->state = ft_state_1(state);
	else if (state->state == STATE_2)
		next->state = ft_state_2(state);
	else if (state->state == STATE_3)
		next->state = ft_state_3(state);
	else if (state->state == STATE_4)
		next->state = ft_state_4(state);
	else if (state->state == STATE_5)
		next->state = ft_state_5(state);
	else if (state->state == STATE_6)
		next->state = ft_state_6(state);
	else if (state->state == STATE_7)
		next->state = ft_state_7(state);
	else if (state->state == STATE_8)
		next->state = ft_state_8(state);
	else if (state->state == STATE_9)
		next->state = ft_state_9(state);
	else if (state->state == STATE_10)
		next->state = ft_state_10(state);
	// printf("next_state : %d\n", next->state);
	linked_state(&state, &next, &token);
	printf("state : %d\n", state->state);
	printf("type : %d\n", state->type);
	if (state->state != STATE_ERR && state->state != STATE_END)
		ft_goto(state, token);
	if (state->state == STATE_END)
		return (STATE_END);
	return (STATE_ERR);
}

int	ft_parser(t_token *token)
{
	t_action_state	*state;

	state_init(&state, &token);
	if (ft_goto(state, token) == STATE_ERR)
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}