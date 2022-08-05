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

void	linked_state(t_action_state **state, t_action_state **next, t_token **token)
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

t_state_num ft_state_0(t_token_type type)
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

t_state_num ft_state_1(t_token_type type)
{
	if (type == DOLLAR)
		return (STATE_END);
	return (STATE_ERR);
}

t_state_num ft_state_2(t_action_state **state, t_token_type type)
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

t_state_num ft_state_3(t_action_state **state, t_token_type type)
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

t_state_num ft_state_4(t_action_state **state, t_token_type type)
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

t_state_num ft_state_5(t_action_state **state, t_token_type type)
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

t_state_num ft_state_6(t_token_type type)
{
	if (type == ID)
		return (STATE_9);
	return (STATE_ERR);
}

t_state_num ft_state_7(t_token_type type)
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

t_state_num ft_state_8(t_action_state **state, t_token_type type)
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

t_state_num ft_state_9(t_action_state **state, t_token_type type)
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

t_state_num ft_state_10(t_action_state **state, t_token_type type)
{
	if (type == DOLLAR)
	{
		reduce_1(state);
		return (STATE_STAY);
	}
	return (STATE_ERR);
}

void ft_goto(t_action_state **state, t_token **token)
{
	t_action_state	*next;
	t_token_type	type;

	next = new_state();
	ft_set_type(&type, state, token);
	if ((*state)->state == STATE_0)
		next->state = ft_state_0(type);
	else if ((*state)->state == STATE_1)
		next->state = ft_state_1(type);
	else if ((*state)->state == STATE_2)
		next->state = ft_state_2(state, type);
	else if ((*state)->state == STATE_3)
		next->state = ft_state_3(state, type);
	else if ((*state)->state == STATE_4)
		next->state = ft_state_4(state, type);
	else if ((*state)->state == STATE_5)
		next->state = ft_state_5(state, type);
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

t_limiter_q	*new_limiter_q()
{
	t_limiter_q	*new;

	new = ft_malloc(sizeof(t_limiter_q));
	new->front = NULL;
	new->rear = NULL;
	new->cnt = 0;
	return (new);
}

t_redir_list	*new_redir_list()
{
	t_redir_list	*new;

	new = ft_malloc(sizeof(t_redir_list));
	new->file_name = NULL;
	new->next = NULL;
	return (new);
}

t_arg_list	*new_arg_list()
{
	t_arg_list	*new;

	new = ft_malloc(sizeof(t_arg_list));
	new->content = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*new_cmd()
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd));
	new->arg = new_arg_list();
	new->lim_q = new_limiter_q();
	new->redir = new_redir_list();
	return (new);
}

t_pipe_line	*new_pipe()
{
	t_pipe_line	*new;

	new = ft_malloc(sizeof(t_pipe_line));
	new->cmd = new_cmd();
	new->next_pipe = NULL;
	return (new);
}

int	ft_parsing(t_pipe_line **pipe, t_token **token)
{
	t_token	*temp;

	if ((*token)->type == ID)
	{
		(*pipe)->cmd->arg->content = (*token)->content;
		(*pipe)->cmd->arg->next = new_arg_list();
		(*pipe)->cmd->arg = (*pipe)->cmd->arg->next;
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
			(*pipe)->cmd->redir->file_name = (*token)->content;
			(*pipe)->cmd->redir->redir_type = REDIR_IN;
			(*pipe)->cmd->redir->next = new_redir_list();
			(*pipe)->cmd->redir = (*pipe)->cmd->redir->next;
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
			(*pipe)->cmd->redir->file_name = (*token)->content;
			(*pipe)->cmd->redir->redir_type = REDIR_OUT;
			(*pipe)->cmd->redir->next = new_redir_list();
			(*pipe)->cmd->redir = (*pipe)->cmd->redir->next;
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
			(*pipe)->cmd->redir->file_name = (*token)->content;
			(*pipe)->cmd->redir->redir_type = REDIR_APPEND;
			(*pipe)->cmd->redir->next = new_redir_list();
			(*pipe)->cmd->redir = (*pipe)->cmd->redir->next;
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
			ft_enqueue(&((*pipe)->cmd->lim_q), (*token)->content);
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
		(*pipe)->next_pipe = new_pipe();
		(*pipe) = (*pipe)->next_pipe;
		return (1);
	}
	return (0);
}

int	ft_parser(t_pipe_head *pipe_head, t_token *token)
{
	t_action_state	*state;
	void			*temp;

	state = new_state();
	state->state = STATE_0;
	temp = token;
	ft_goto(&state, &token);
	token = temp;
	pipe_head->cnt_pipe = 0;
	temp = pipe_head->head;
	if (state->state == STATE_ERR)
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		return (-1);
	}
	else
	{
		pipe_head->head = new_pipe();
		while (token != NULL)
			if (ft_parsing(&(pipe_head->head), &token) == 1)
				pipe_head->cnt_pipe++;
		pipe_head->head = temp;
	}
	ft_print(pipe_head->head);
	return (0);
}