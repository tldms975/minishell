/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:32:41 by sielee            #+#    #+#             */
/*   Updated: 2022/08/16 13:40:00 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_error(char *file_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file_name, STDERR_FILENO);
	ft_perror("");
}

static void	ft_redir_out(t_token_type type, char *file_name, \
t_executor *exec)
{
	int	tmp;

	if (type == REDIR_OUT)
	{
		if (!(exec->is_heredoc) || \
		(((exec->is_heredoc) && (exec->fd_read != exec->heredoc_fd[READ]))))
			ft_close(exec->fd_write);
		tmp = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp < 0)
			ft_print_error(file_name);
		else
			exec->fd_write = tmp;
		printf("files[%s]'s fd: %d\n", file_name, tmp);//
	}
	else if (type == REDIR_APPEND)
	{
		if (!(exec->is_heredoc) || \
		(((exec->is_heredoc) && (exec->fd_read != exec->heredoc_fd[READ]))))
			ft_close(exec->fd_write);
		tmp = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tmp < 0)
			ft_print_error(file_name);
		else
			exec->fd_write = tmp;
		printf("file[%s]'s fd: %d\n", file_name, tmp);//
	}
}

static void	ft_redir_in(t_token_type type, char *file_name, \
t_executor *exec)
{
	int	tmp;

	if (type == REDIR_IN)
	{
		tmp = open(file_name, O_RDONLY);
		if (tmp < 0)
		{
			ft_print_error(file_name);
			return ;
		}
		if (!(exec->is_heredoc) || \
		(((exec->is_heredoc) && (exec->fd_read != exec->heredoc_fd[READ]))))
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
	printf("redir~~\n");//
	while (redir)
	{
		printf("type: %d\n", redir->type);//
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			ft_redir_in(redir->type, redir->file_name, exec);
		else
			ft_redir_out(redir->type, redir->file_name, exec);
		redir = redir->next;
	}
	////
	printf("final(%d, %d)\n", exec->fd_read, exec->fd_write);//
}
