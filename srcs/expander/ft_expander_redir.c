/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:59:58 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 17:59:59 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
