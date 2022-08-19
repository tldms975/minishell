/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:55:39 by sielee            #+#    #+#             */
/*   Updated: 2022/08/19 15:02:52 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_write_in_pipe(t_limiter_q *lim_q, t_executor *exec, \
t_envp_list *env_list)
{
	char	*line;
	char	*limiter;
	t_fuc	funct;

	line = NULL;
	ft_expander_heredoc_table(&funct);
	while (1)
	{
		limiter = lim_q->front->data;
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, (ft_strlen(limiter) + 1)) == 0)
		{
			ft_free((void **) &line);
			break ;
		}
		if (lim_q->front->state == QOUTE_OFF)
			ft_expander_heredoc(&line, env_list, funct);
		write(exec->heredoc_fd[WRITE], line, ft_strlen(line));
		write(exec->heredoc_fd[WRITE], "\n", 1);
		ft_free((void **) &line);
	}
	ft_dequeue(lim_q);
	ft_close(exec->heredoc_fd[WRITE]);
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
			ft_dequeue(lim_q);
		else if (ft_strncmp(line, limiter, (ft_strlen(limiter) + 1)) == 0)
		{
			ft_free((void **) &line);
			ft_dequeue(lim_q);
		}
	}
	if (line)
		ft_free((void **) &line);
}

void	ft_check_heredoc(t_limiter_q *lim_q, t_executor *exec, \
t_envp_list *env_list)
{
	pid_t	pid;

	if (lim_q->cnt == 0)
	{
		exec->is_heredoc = FALSE;
	}
	else
	{
		exec->is_heredoc = TRUE;
		ft_heredoc_sgh();
		ft_ready_last_heredoc(lim_q);
		ft_pipe(exec->heredoc_fd);
		pid = ft_fork();
		if (pid == 0)
		{
			ft_heredoc_write_in_pipe(lim_q, exec, env_list);
			exit(EXIT_FAILURE);
		}
		wait(0);
		ft_default_signal();
		ft_close(exec->heredoc_fd[WRITE]);
		printf("heredoc(%d, %d)\n", exec->heredoc_fd[READ], exec->heredoc_fd[WRITE]);//
	}
}
