/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:55:39 by sielee            #+#    #+#             */
/*   Updated: 2022/08/15 06:12:42 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_read_heredoc(t_executor *exec, char *limiter)
{
	char	*line;

	line = NULL;
	while (ft_strncmp(line, limiter, (ft_strlen(limiter) + 1)) != 0)
	{
		line = readline("> ");
		if (!line)
			break ;
		write(exec->fd_write, line, ft_strlen(line));
		write(exec->fd_write, "\n", 1);
		free(line);
	}
}

void	ft_heredoc(t_limiter_q	*lim_q, t_executor *exec)
{
	ft_read_heredoc(exec, lim_q->front->data);
	ft_dequeue(lim_q);
	ft_close(exec->fd_write);
	while (!ft_is_empty_q(lim_q))
		ft_check_heredoc(lim_q, exec);
	exec->fd_read = exec->heredoc_fd[READ];
}

void	ft_check_heredoc(t_limiter_q *lim_q, t_executor *exec)
{
	if (lim_q->cnt > 0)
	{
		ft_pipe(exec->heredoc_fd);
		ft_close(exec->heredoc_fd[READ]);//부모에서는 닫아주는게 맞다
		exec->fd_write = exec->heredoc_fd[WRITE];
		ft_heredoc(lim_q, exec);
	}
}
