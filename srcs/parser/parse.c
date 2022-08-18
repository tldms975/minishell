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

int	ft_arg_pipe(t_token **token)
{
	t_token	*temp;

	free((*token)->content);
	temp = (*token);
	(*token) = (*token)->next;
	free(temp);
	return (1);
}

int	ft_redir(t_pipe_node **pipe, t_token **token)
{
	if ((*token)->type == REDIR_IN)
	{
		if (ft_arg_redir_in(pipe, token) == -1)
			return (-1);
	}
	else if ((*token)->type == REDIR_OUT)
	{
		if (ft_arg_redir_out(pipe, token) == -1)
			return (-1);
	}
	else if ((*token)->type == REDIR_APPEND)
	{
		if (ft_arg_redir_append(pipe, token) == -1)
			return (-1);
	}
	else if ((*token)->type == REDIR_HEREDOC)
	{
		if (ft_arg_heredoc(pipe, token) == -1)
			return (-1);
	}
	else if ((*token)->type == PIPE)
		if (ft_arg_pipe(token) == 1)
			return (1);
	return (0);
}

int	ft_parsing(t_pipe_node **pipe, t_token **token)
{
	int	ret;

	if ((*token)->type == ID)
		ft_arg_id(pipe, token);
	else
	{
		ret = ft_redir(pipe, token);
		if (ret == -1)
			return (-1);
		else if (ret == 1)
			return (1);
	}
	return (0);
}

void	ft_parser_sub(t_pipe_list **pipe_list, t_token **token, void *temp)
{
	*token = temp;
	ft_enqueue_pipe(pipe_list);
	while (*token != NULL)
	{
		if (ft_parsing(&((*pipe_list)->tail), token) == 1)
			ft_enqueue_pipe(pipe_list);
	}
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
		ft_state_free(&temp_state);
		return (-1);
	}
	else
		ft_parser_sub(&pipe_list, &token, temp);
	ft_state_free(&temp_state);
	ft_expand(pipe_list, env);
	return (0);
}
