/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state5to9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:37:06 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 18:37:08 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state_num	ft_state_5(t_action_state **state, t_token_type type)
{
	if (type == REDIR_APPEND || type == REDIR_HEREDOC
		|| type == REDIR_IN || type == REDIR_OUT
		|| type == PIPE || type == ID
		|| type == DOLLAR)
	{
		reduce_7(state);
		return (STATE_STAY);
	}
	return (STATE_ERR);
}

t_state_num	ft_state_6(t_token_type type)
{
	if (type == ID)
		return (STATE_9);
	return (STATE_ERR);
}

t_state_num	ft_state_7(t_token_type type)
{
	if (type == REDIR_APPEND || type == REDIR_HEREDOC
		|| type == REDIR_IN || type == REDIR_OUT)
		return (STATE_6);
	else if (type == ID)
		return (STATE_5);
	else if (type == PIPE_LINE)
		return (STATE_10);
	else if (type == COMMAND)
		return (STATE_2);
	else if (type == REDIRECTION)
		return (STATE_4);
	else if (type == ELEM)
		return (STATE_3);
	return (STATE_ERR);
}

t_state_num	ft_state_8(t_action_state **state, t_token_type type)
{
	if (type == REDIR_APPEND || type == REDIR_HEREDOC
		|| type == REDIR_IN || type == REDIR_OUT
		|| type == PIPE || type == ID
		|| type == DOLLAR)
	{
		reduce_4(state);
		return (STATE_STAY);
	}
	return (STATE_ERR);
}

t_state_num	ft_state_9(t_action_state **state, t_token_type type)
{
	if (type == REDIR_APPEND || type == REDIR_HEREDOC
		|| type == REDIR_IN || type == REDIR_OUT
		|| type == PIPE || type == ID
		|| type == DOLLAR)
	{
		reduce_5(state);
		return (STATE_STAY);
	}
	return (STATE_ERR);
}
