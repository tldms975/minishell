/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:32:41 by sielee            #+#    #+#             */
/*   Updated: 2022/08/13 17:05:44 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirection(enum e_token_type type, const char *file_name, \
t_executor *exec)
{
	if (type == REDIR_IN)
	{
		ft_close(exec->fd_read);
		exec->fd_read = ft_open(file_name, O_RDONLY);
	}
	else if(type == REDIR_HEREDOC)
	{
		ft_close(exec->fd_read);
		exec->fd_read = exec->heredoc_fd[READ];
	}
	else if (type == REDIR_OUT)
	{
		ft_close(exec->fd_read);
		exec->fd_write = ft_open(file_name, O_WRONLY | O_CREAT | O_TRUNC);
	}
	else if (type == REDIR_APPEND)
	{
		ft_close(exec->fd_read);
		exec->fd_write = ft_open(file_name, O_WRONLY | O_CREAT | O_APPEND);
	}
}
