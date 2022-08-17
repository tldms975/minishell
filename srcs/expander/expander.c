/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/08/17 16:50:46 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expander_arg(t_arg_node **node, t_envp_list *list, t_fuc funct)
{
	t_expand_state		next_state;
	char				next_char;
	t_fuc_exp			function;
	t_buffer			*buffer;

	ft_expander_init((*node)->content, &buffer, list);
	while (1)
	{
		next_char = (buffer->content)[buffer->index];
		next_state = check_expand_type(next_char);
		if (next_state == EX_NULL)
			break ;
		function = (funct.function)[buffer->curr_state][next_state];
		if (function(buffer) == -1)
			return ;
	}
	if (buffer->curr_state == EX_NORMAL)
		new_save(&buffer);
	ft_free((void **)(&(*node)->content));
	if (buffer->save_content != NULL)
		(*node)->content = buffer->save_content;
	else
		(*node)->content = NULL;
	free(buffer);
}

void	ft_del_node_arg(t_arg_node **temp_arg, t_arg_node **front)
{
	t_arg_node	*temp;

	temp = (*temp_arg)->next;
	if ((*temp_arg)->content == NULL)
	{
		if ((*temp_arg)->prev == NULL)
			*front = (*front)->next;
		else if ((*temp_arg)->prev != NULL)
			(*temp_arg)->prev->next = (*temp_arg)->next;
		if ((*temp_arg)->next != NULL)
			(*temp_arg)->next->prev = (*temp_arg)->prev;
		ft_free((void **)temp_arg);
	}
	*temp_arg = temp;
}

void	ft_expander_redir(t_redir_node **node, t_envp_list *list, t_fuc funct)
{
	t_expand_state		next_state;
	char				next_char;
	t_fuc_exp			function;
	t_buffer			*buffer;

	ft_expander_init((*node)->file_name, &buffer, list);
	while (1)
	{
		next_char = (buffer->content)[buffer->index];
		next_state = check_expand_type(next_char);
		if (next_state == EX_NULL)
			break ;
		function = (funct.function)[buffer->curr_state][next_state];
		if (function(buffer) == -1)
			return ;
	}
	if (buffer->curr_state == EX_NORMAL)
		new_save(&buffer);
	ft_free((void **)(&(*node)->file_name));
	if (buffer->save_content != NULL)
		(*node)->file_name = buffer->save_content;
	else
		(*node)->file_name = NULL;
	free(buffer);
}

void	ft_del_node_redir(t_redir_node **temp_arg, t_redir_node **front)
{
	t_redir_node	*temp;

	temp = (*temp_arg)->next;
	if ((*temp_arg)->file_name == NULL)
	{
		if ((*temp_arg)->prev == NULL)
			*front = (*front)->next;
		else if ((*temp_arg)->prev != NULL)
			(*temp_arg)->prev->next = (*temp_arg)->next;
		if ((*temp_arg)->next != NULL)
			(*temp_arg)->next->prev = (*temp_arg)->prev;
		ft_free((void **)temp_arg);
	}
	*temp_arg = temp;
}

void	ft_exp_lim_init(t_buffer **buffer, t_limiter_node **node)
{
	*buffer = ft_malloc(sizeof(t_buffer));
	(*buffer)->content = (*node)->data;
	(*buffer)->save_content = NULL;
	(*buffer)->curr_state = check_expand_lim_type(*((*node)->data));
	(*buffer)->index = 1;
	if ((*buffer)->curr_state != EX_SI_QUO && (*buffer)->curr_state != EX_DO_QUO)
		(*node)->state = QOUTE_OFF;
	else
	{
		(*buffer)->content++;
		(*buffer)->index = 0;
		(*node)->state = QOUTE_ON;
	}
}

void	ft_expander_lim(t_limiter_node **node, t_fuc funct)
{
	t_expand_state		next_state;
	char				next_char;
	t_fuc_exp			function;
	t_buffer			*buffer;

	ft_exp_lim_init(&buffer, node);
	while (1)
	{
		next_char = (buffer->content)[buffer->index];
		next_state = check_expand_lim_type(next_char);
		if ((next_state == EX_SI_QUO || next_state == EX_DO_QUO) && (*node)->state == QOUTE_OFF)
			(*node)->state = QOUTE_ON;
		if (next_state == EX_NULL)
			break ;
		function = (funct.function)[buffer->curr_state][next_state];
		if (function(buffer) == -1)
			return ;
	}
	if (buffer->curr_state == EX_NORMAL)
		new_save(&buffer);
	ft_free((void **)(&(*node)->data));
	(*node)->data = buffer->save_content;
	free(buffer);
}

void	ft_expand(t_pipe_list *pipe, t_envp_list *env)
{
	t_pipe_node		*temp_pipe;
	t_arg_node		*temp_arg;
	t_redir_node	*temp_redir;
	t_limiter_node	*temp_lim;
	t_fuc			funct;

	ft_expander_table(&funct);
	temp_pipe = pipe->head;
	while (temp_pipe != NULL)
	{
		temp_arg = temp_pipe->arg_list->front;
		while (temp_arg != NULL)
		{
			ft_expander_arg(&temp_arg, env, funct);
			ft_del_node_arg(&temp_arg, &(temp_pipe->arg_list->front));
		}
		temp_redir = temp_pipe->redir_list->front;
		while (temp_redir != NULL)
		{
			if (temp_redir->type != REDIR_HEREDOC)
			{
				ft_expander_redir(&temp_redir, env, funct);
				ft_del_node_redir(&temp_redir, &(temp_pipe->redir_list->front));
			}
			else
				temp_redir = temp_redir->next;
		}
		temp_lim = temp_pipe->lim_q->front;
		while (temp_lim != NULL)
		{
			ft_expander_lim(&temp_lim, funct);
			temp_lim = temp_lim->next;
		}
		temp_pipe = temp_pipe->next;
	}
}