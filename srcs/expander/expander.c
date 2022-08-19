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

void	ft_while_arg(t_pipe_node **temp_pipe, t_envp_list *env, t_fuc *funct)
{
	t_arg_node	*temp_arg;

	temp_arg = (*temp_pipe)->arg_list->front;
	while (temp_arg != NULL)
	{
		ft_expander_arg(&temp_arg, env, *funct);
		ft_del_node_arg(&temp_arg, &((*temp_pipe)->arg_list->front));
	}
}

void	ft_while_redir(t_pipe_node **temp_pipe, t_envp_list *env, t_fuc *funct)
{
	t_redir_node	*temp_redir;

	temp_redir = (*temp_pipe)->redir_list->front;
	while (temp_redir != NULL)
	{
		if (temp_redir->type != REDIR_HEREDOC)
		{
			ft_expander_redir(&temp_redir, env, *funct);
			temp_redir = temp_redir->next;
		}
		else
			temp_redir = temp_redir->next;
	}
}

void	ft_expand(t_pipe_list *pipe, t_envp_list *env)
{
	t_pipe_node		*temp_pipe;
	t_limiter_node	*temp_lim;
	t_fuc			funct;

	ft_expander_table(&funct);
	temp_pipe = pipe->head;
	while (temp_pipe != NULL)
	{
		ft_while_arg(&temp_pipe, env, &funct);
		ft_while_redir(&temp_pipe, env, &funct);
		temp_lim = temp_pipe->lim_q->front;
		while (temp_lim != NULL)
		{
			ft_expander_lim(&temp_lim, funct);
			temp_lim = temp_lim->next;
		}
		temp_pipe = temp_pipe->next;
	}
}
