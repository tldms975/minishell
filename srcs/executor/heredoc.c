/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:55:39 by sielee            #+#    #+#             */
/*   Updated: 2022/08/17 01:33:49 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_write_in_pipe(t_limiter_q *lim_q, t_executor *exec)
{
	char	*line;
	char	*limiter;

	line = NULL;
	while (1)
	{
		limiter = lim_q->front->data;
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, (ft_strlen(limiter) + 1)) == 0)
			break ;
		write(exec->heredoc_fd[WRITE], line, ft_strlen(line));
		write(exec->heredoc_fd[WRITE], "\n", 1);
		free(line);
	}
	ft_dequeue(lim_q);
	ft_close(exec->r_pipe_fd[WRITE]);
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
	{
		exec->is_heredoc = FALSE;
	}
	else
	{
		exec->is_heredoc = TRUE;
		ft_ready_last_heredoc(lim_q);
		ft_pipe(exec->heredoc_fd);
		ft_heredoc_write_in_pipe(lim_q, exec);
		printf("heredoc(%d, %d)\n", exec->heredoc_fd[READ], exec->heredoc_fd[WRITE]);//
	}
}
