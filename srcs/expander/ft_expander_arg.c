/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:59:46 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 17:59:48 by iyun             ###   ########.fr       */
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
