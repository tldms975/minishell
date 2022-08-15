/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:32:41 by sielee            #+#    #+#             */
/*   Updated: 2022/08/15 19:47:26 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redir_out(t_token_type type, const char *file_name, t_executor *exec)
{
	if (type == REDIR_OUT)
	{
		if (!(exec->is_heredoc))
			ft_close(exec->fd_read);
		else if ( (exec->fd_read != exec->heredoc_fd[READ]))
			ft_close(exec->fd_read);
		exec->fd_write = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (type == REDIR_APPEND)
	{
		if (!(exec->is_heredoc))
			ft_close(exec->fd_read);
		else if (exec->fd_read != exec->heredoc_fd[READ])
			ft_close(exec->fd_read);
		exec->fd_write = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
}

static void	ft_redir_in(t_token_type type, const char *file_name, t_executor *exec)
{
	int	tmp;

	if (type == REDIR_IN)
	{
		tmp = open(file_name, O_RDONLY);
		if (tmp < 0)
		{
			ft_perror("open");
			return ;
		}
		if (!(exec->is_heredoc))
			ft_close(exec->fd_read);
		else if (exec->fd_read != exec->heredoc_fd[READ])
			ft_close(exec->fd_read);
		exec->fd_read = tmp;
	}
	else if (type == REDIR_HEREDOC)
	{
		if (exec->fd_read != exec->heredoc_fd[READ])
			ft_close(exec->fd_read);
		exec->fd_read = exec->heredoc_fd[READ];
	}
}

void	ft_redirection(t_redir_node *redir, t_executor *exec)
{
	if (exec->is_heredoc == TRUE)
		ft_close(exec->heredoc_fd[WRITE]);
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			ft_redir_in(redir->type, redir->file_name, exec);
		else
			ft_redir_out(redir->type, redir->file_name, exec);
		redir = redir->next;
	}
}
