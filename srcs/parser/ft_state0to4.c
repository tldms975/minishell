/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state0to4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:37:02 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 18:37:03 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state_num	ft_state_0(t_token_type type)
{
	if (type == REDIR_APPEND || type == REDIR_HEREDOC
		|| type == REDIR_IN || type == REDIR_OUT)
		return (STATE_6);
	else if (type == ID)
		return (STATE_5);
	else if (type == PIPE_LINE)
		return (STATE_1);
	else if (type == COMMAND)
		return (STATE_2);
	else if (type == REDIRECTION)
		return (STATE_4);
	else if (type == ELEM)
		return (STATE_3);
	return (STATE_ERR);
}

t_state_num	ft_state_1(t_token_type type)
{
	if (type == DOLLAR)
		return (STATE_END);
	return (STATE_ERR);
}

t_state_num	ft_state_2(t_action_state **state, t_token_type type)
{
	if (type == PIPE)
		return (STATE_7);
	else if (type == REDIR_APPEND || type == REDIR_HEREDOC
		|| type == REDIR_IN || type == REDIR_OUT)
		return (STATE_6);
	else if (type == ID)
		return (STATE_5);
	else if (type == REDIRECTION)
		return (STATE_4);
	else if (type == ELEM)
		return (STATE_8);
	else if (type == DOLLAR)
	{
		reduce_2(state);
		return (STATE_STAY);
	}
	return (STATE_ERR);
}

t_state_num	ft_state_3(t_action_state **state, t_token_type type)
{
	if (type == REDIR_APPEND || type == REDIR_HEREDOC
		|| type == REDIR_IN || type == REDIR_OUT
		|| type == PIPE || type == ID
		|| type == DOLLAR)
	{
		reduce_3(state);
		return (STATE_STAY);
	}
	return (STATE_ERR);
}

t_state_num	ft_state_4(t_action_state **state, t_token_type type)
{
	if (type == REDIR_APPEND || type == REDIR_HEREDOC
		|| type == REDIR_IN || type == REDIR_OUT
		|| type == PIPE || type == ID
		|| type == DOLLAR)
	{
		reduce_6(state);
		return (STATE_STAY);
	}
	return (STATE_ERR);
}
