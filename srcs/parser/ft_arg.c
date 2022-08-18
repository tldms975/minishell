/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:36:54 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 18:36:56 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arg_id(t_pipe_node **pipe, t_token **token)
{
	t_token	*temp;

	ft_enqueue_arg(pipe, (*token)->content);
	temp = *token;
	(*token) = (*token)->next;
	free(temp);
}

int	ft_arg_redir_in(t_pipe_node **pipe, t_token **token)
{
	t_token	*temp;

	free((*token)->content);
	temp = (*token);
	(*token) = (*token)->next;
	free(temp);
	if ((*token)->type == ID)
	{
		ft_enqueue_redir(pipe, REDIR_IN, (*token)->content);
		temp = *token;
		(*token) = (*token)->next;
		free(temp);
	}
	else
		return (-1);
	return (0);
}

int	ft_arg_redir_out(t_pipe_node **pipe, t_token **token)
{
	t_token	*temp;

	free((*token)->content);
	temp = (*token);
	(*token) = (*token)->next;
	free(temp);
	if ((*token)->type == ID)
	{
		ft_enqueue_redir(pipe, REDIR_OUT, (*token)->content);
		temp = *token;
		(*token) = (*token)->next;
		free(temp);
	}
	else
		return (-1);
	return (0);
}

int	ft_arg_redir_append(t_pipe_node **pipe, t_token **token)
{
	t_token	*temp;

	free((*token)->content);
	temp = (*token);
	(*token) = (*token)->next;
	free(temp);
	if ((*token)->type == ID)
	{
		ft_enqueue_redir(pipe, REDIR_APPEND, (*token)->content);
		temp = *token;
		(*token) = (*token)->next;
		free(temp);
	}
	else
		return (-1);
	return (0);
}

int	ft_arg_heredoc(t_pipe_node **pipe, t_token **token)
{
	t_token	*temp;

	free((*token)->content);
	temp = (*token);
	(*token) = (*token)->next;
	free(temp);
	if ((*token)->type == ID)
	{
		ft_enqueue_redir(pipe, REDIR_HEREDOC, (*token)->content);
		temp = *token;
		(*token) = (*token)->next;
		free(temp);
	}
	else
		return (-1);
	return (0);
}
