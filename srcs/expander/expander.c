/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/07/25 20:16:48 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expander_arg(t_arg_node	**node, t_envp_list *list, t_fuc funct)
{
	t_expand_state		next_state;
	char				next_char;
	t_fuc_exp			function;
	t_buffer			*buffer;

	ft_expander_init(node, &buffer, list);
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
	free((*node)->content);
	if (buffer->save_content != NULL)
		(*node)->content = buffer->save_content;
	else
		(*node)->content = NULL;
	printf("arg_prev : %p\n", (*node)->prev);
	printf("arg_node : %p\n", (*node));
	printf("arg_next : %p\n", (*node)->next);
	free(buffer);
}

void	ft_expand(t_pipe_list *pipe, t_envp_list *env)
{
	t_pipe_node		*temp_pipe;
	t_arg_node		*temp_arg;
	t_redir_node	*temp_redir;
	t_limiter_node	*temp_lim;
	t_fuc			funct;

	printf("arg_head : %p\n", pipe->head->arg_list->front);
	printf("arg_head_next : %p\n", pipe->head->arg_list->front->next);
	ft_expander_table(&funct);
	temp_pipe = pipe->head;
	while (temp_pipe != NULL)
	{
		temp_arg = temp_pipe->arg_list->front;
		while (temp_arg != NULL)
		{
			printf("arg_head in : %p\n", pipe->head->arg_list->front);
			ft_expander_arg(&temp_arg, env, funct);
			if (temp_arg->content == NULL)
			{
				if (temp_arg->prev != NULL)
					temp_arg->prev->next = temp_arg->next;
				if (temp_arg->next != NULL)
					temp_arg->next->prev = temp_arg->prev;
				ft_free((void **)&temp_arg);
			}
			printf("arg_head in : %p\n", pipe->head->arg_list->front);
			printf("temp in : %p\n", temp_arg);
			if (temp_arg != NULL)
				temp_arg = temp_arg->next;
		}
		temp_redir = temp_pipe->redir_list->front;
		while (temp_redir != NULL)
		{
			temp_redir = temp_redir->next;
		}
		temp_lim = temp_pipe->lim_q->front;
		while (temp_lim != NULL)
		{
			temp_lim = temp_lim->next;
		}
		temp_pipe = temp_pipe->next;
	}
}