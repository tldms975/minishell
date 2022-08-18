/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:32:41 by sielee            #+#    #+#             */
/*   Updated: 2022/08/18 22:26:21 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redir_out(t_token_type type, char *file_name, \
t_executor *exec)
{
	if (type == REDIR_OUT)
	{
		if (!(exec->is_heredoc) || \
		(((exec->is_heredoc) && (exec->fd_read != exec->heredoc_fd[READ]))))
			ft_close(exec->fd_write);
		exec->fd_write = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("files[%s]'s fd: %d\n", file_name, exec->fd_write);//
	}
	else if (type == REDIR_APPEND)
	{
		if (!(exec->is_heredoc) || \
		(((exec->is_heredoc) && (exec->fd_read != exec->heredoc_fd[READ]))))
			ft_close(exec->fd_write);
		exec->fd_write = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		printf("files[%s]'s fd: %d\n", file_name, exec->fd_write);//
	}
}

static void	ft_redir_in(t_token_type type, char *file_name, \
t_executor *exec)
{
	if (type == REDIR_IN)
	{
		if (!(exec->is_heredoc) || \
		(((exec->is_heredoc) && (exec->fd_read != exec->heredoc_fd[READ]))))
			ft_close(exec->fd_read);
		exec->fd_read = open(file_name, O_RDONLY);
		printf("file[%s]'s fd: %d\n", file_name, exec->fd_read);//
	}
	else if (type == REDIR_HEREDOC)
	{
		if (exec->fd_read != exec->heredoc_fd[READ])
			ft_close(exec->fd_read);
		exec->fd_read = exec->heredoc_fd[READ];
	}
}

int	ft_redirection(t_arg_node *arg, t_redir_node *redir, t_executor *exec)
{
	int	valid_code;

	printf("redir~~\n");//
	while (redir)
	{
		valid_code = ft_check_valid_redir_files(arg, redir, exec);
		if (valid_code == EXIT_SUCCESS)
		{
			if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
				ft_redir_in(redir->type, redir->file_name, exec);
			else
				ft_redir_out(redir->type, redir->file_name, exec);
		}
		else if (valid_code == EXIT_FAILURE)
		{
			exec->in = DO_NOT_EXE;
			return (EXIT_FAILURE);
		}
		redir = redir->next;
	}
	printf("final(%d, %d)\n", exec->fd_read, exec->fd_write);//
	return (EXIT_SUCCESS);
}
