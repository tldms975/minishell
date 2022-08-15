/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/07/25 20:16:48 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parsing(t_pipe_node **pipe, t_token **token)
{
	t_token	*temp;

	if ((*token)->type == ID)
	{
		ft_enqueue_arg(pipe, (*token)->content);
		temp = *token;
		(*token) = (*token)->next;
		free(temp);
	}
	else if ((*token)->type == REDIR_IN)
	{
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
	}
	else if ((*token)->type == REDIR_OUT)
	{
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
	}
	else if ((*token)->type == REDIR_APPEND)
	{
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
	}
	else if ((*token)->type == REDIR_HEREDOC)
	{
		free((*token)->content);
		temp = (*token);
		(*token) = (*token)->next;
		free(temp);
		if ((*token)->type == ID)
		{
			ft_enqueue(&((*pipe)->lim_q), (*token)->content);
			temp = *token;
			(*token) = (*token)->next;
			free(temp);
		}
		else
			return (-1);
	}
	else if ((*token)->type == PIPE)
	{
		free((*token)->content);
		temp = (*token);
		(*token) = (*token)->next;
		free(temp);
		return (1);
	}
	return (0);
}

int	ft_parser(t_pipe_list *pipe_list, t_token *token, t_envp_list *env)
{
	t_action_state	*state;
	t_action_state	*temp_state;
	void			*temp;

	state = new_state();
	if (token != NULL)
		state->state = STATE_0;
	else
		state->state = STATE_1;
	temp = token;
	temp_state = state;
	ft_goto(&state, &token);
	if (state->state == STATE_ERR)
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		return (-1);
	}
	else
	{
		token = temp;
		ft_enqueue_pipe(&pipe_list);
		while (token != NULL)
		{
			if (ft_parsing(&(pipe_list->tail), &token) == 1)
				ft_enqueue_pipe(&pipe_list);
		}
	}
	ft_state_free(&temp_state);
	ft_expand(pipe_list, env);
	return (0);
}