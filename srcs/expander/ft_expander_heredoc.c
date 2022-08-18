/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:59:50 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 17:59:51 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	buffer_heredoc_init(char *str, t_buffer **buffer, t_envp_list *list)
{
	*buffer = ft_malloc(sizeof(t_buffer));
	(*buffer)->content = str;
	(*buffer)->curr_state = check_expand_heredoc_type(*(str));
	(*buffer)->save_content = NULL;
	(*buffer)->index = 1;
	(*buffer)->env_list = list;
	if ((*buffer)->curr_state == EX_DOLLAR
		&& (check_expand_type(((*buffer)->content)[(*buffer)->index])
		== EX_NULL))
	{
		(*buffer)->curr_state = EX_NORMAL;
		return (1);
	}
	return (0);
}

void	ft_expander_heredoc(char **str, t_envp_list *list, t_fuc funct)
{
	t_expand_state		next_state;
	char				next_char;
	t_fuc_exp			function;
	t_buffer			*buffer;

	buffer_heredoc_init(*str, &buffer, list);
	while (1)
	{
		next_char = (buffer->content)[buffer->index];
		next_state = check_expand_heredoc_type(next_char);
		if (next_state == EX_NULL)
			break ;
		function = (funct.function)[buffer->curr_state][next_state];
		if (function(buffer) == -1)
			return ;
	}
	if (buffer->curr_state == EX_NORMAL)
		new_save(&buffer);
	ft_free((void **)str);
	if (buffer->save_content != NULL)
		*str = buffer->save_content;
	else
		*str = ft_strdup("");
	free(buffer);
}
