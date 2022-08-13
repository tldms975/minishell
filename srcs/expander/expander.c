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

	buffer = ft_malloc(sizeof(t_buffer));
	buffer->content = (*node)->content;
	buffer->curr_state = check_expand_type(*((*node)->content));
	buffer->index = 1;
	buffer->env_list = list;
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
	(*node)->content = buffer->save_content;
	printf("save-2 : %p\n", buffer->save_content);
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
			printf("next!\n");//
			ft_expander_arg(&temp_arg, env, funct);
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