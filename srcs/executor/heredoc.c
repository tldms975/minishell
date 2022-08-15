/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:55:39 by sielee            #+#    #+#             */
/*   Updated: 2022/08/15 16:55:42 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_write_in_pipe(t_limiter_q *lim_q, t_executor *exec)
{
	char	*line;
	char	*limiter;

	line = NULL;
	while (ft_strncmp(line, limiter, (ft_strlen(limiter) + 1)) != 0)
	{
		limiter = lim_q->front->data;
		line = readline("> ");
		if (!line)
			break ;
		write(exec->fd_write, line, ft_strlen(line));
		write(exec->fd_write, "\n", 1);
		free(line);
	}
	ft_dequeue(lim_q);
}

static void	ft_ready_last_heredoc(t_limiter_q *lim_q)
{
	char	*line;
	char	*limiter;

	line = NULL;
	while (lim_q->front->next)
	{
		limiter = lim_q->front->data;
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, (ft_strlen(limiter) + 1)) == 0)
			ft_dequeue(lim_q);
		free(line);
	}
}

void	ft_check_heredoc(t_limiter_q *lim_q, t_executor *exec)
{
	if (lim_q->cnt == 0)
		return ;
	exec->is_heredoc = TRUE;
	ft_ready_last_heredoc(lim_q);
	ft_pipe(exec->heredoc_fd);
	ft_close(exec->heredoc_fd[READ]);
	exec->fd_write = exec->heredoc_fd[WRITE];
	ft_heredoc_write_in_pipe(lim_q, exec);
}
