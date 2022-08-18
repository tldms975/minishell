/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:37:09 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 18:37:10 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	choose_type(t_token *new)
{
	if (!ft_strncmp(new->content, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(new->content, "<", 2))
		return (REDIR_IN);
	else if (!ft_strncmp(new->content, ">", 2))
		return (REDIR_OUT);
	else if (!ft_strncmp(new->content, "<<", 3))
		return (REDIR_HEREDOC);
	else if (!ft_strncmp(new->content, ">>", 3))
		return (REDIR_APPEND);
	else if (ft_check_meta(*(new->content)) == NON_META)
		return (ID);
	return (ERR);
}

t_token	*new_content(t_lexer *lexer)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token));
	new->next = NULL;
	new->content = ft_substr(lexer->last_save_addr, 0, lexer->index);
	if (!new->content)
		exit (-1);
	new->type = choose_type(new);
	if (ft_check_type((lexer->last_save_addr)[lexer->index]) != ST_NULL)
	{
		lexer->last_save_addr += lexer->index;
		lexer->index = 1;
	}
	if (lexer->head)
		lexer->tail->next = new;
	else
		lexer->head = new;
	return (new);
}

void	ft_token_free(t_lexer *lexer)
{
	void	*temp;

	while (lexer->head != NULL)
	{
		temp = lexer->head;
		if (lexer->head->content != NULL)
			free(lexer->head->content);
		lexer->head = lexer->head->next;
		ft_free((void **)&temp);
	}
}
