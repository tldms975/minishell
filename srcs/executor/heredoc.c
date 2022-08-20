/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:55:39 by sielee            #+#    #+#             */
/*   Updated: 2022/08/20 18:51:39 by sielee           ###   ########seoul.kr  */
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
t_envp_list *env_list, int *is_heredoc_in_pipe)
{
	pid_t	pid;
	int		stat;

	if (lim_q->cnt == 0)
		exec->is_heredoc = FALSE;
	else
	{
		exec->is_heredoc = TRUE;
		*is_heredoc_in_pipe = TRUE;
		ft_pipe(exec->heredoc_fd);
		ft_sgh_ign();
		pid = ft_fork();
		if (pid == 0)
		{
			ft_heredoc_sgh();
			ft_ready_last_heredoc(lim_q);
			ft_close(exec->heredoc_fd[READ]);
			ft_heredoc_write_in_pipe(lim_q, exec, env_list);
			exit (EXIT_SUCCESS);
		}
		waitpid(pid, &stat, 0);
		exec->heredoc_exit = ft_get_child_exit_status(stat);
		ft_default_signal();
	}
}
