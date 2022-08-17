/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:55:39 by sielee            #+#    #+#             */
/*   Updated: 2022/08/18 01:24:52 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_escape_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		printf("sigint in heredoc\n");
	}
}
void	ft_heredoc_sgh()
{
	signal(SIGINT, ft_escape_heredoc);
}

static void	ft_heredoc_write_in_pipe(t_limiter_q *lim_q, t_executor *exec, \
t_envp_list *env_list)
{
	char	*line;
	char	*limiter;

	line = NULL;
	while (1)
	{
		limiter = lim_q->front->data;
		line = readline("> ");
		if (!line)
		{

			break ;
		}
		if (ft_strncmp(line, limiter, (ft_strlen(limiter) + 1)) == 0)
			break ;
		write(exec->heredoc_fd[WRITE], line, ft_strlen(line));
		write(exec->heredoc_fd[WRITE], "\n", 1);
		free(line);
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
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			ft_dequeue(lim_q);
		}
		else if (ft_strncmp(line, limiter, (ft_strlen(limiter) + 1)) == 0)
			ft_dequeue(lim_q);
		free(line);
	}
}

void	ft_check_heredoc(t_limiter_q *lim_q, t_executor *exec, t_envp_list *env_list)
{
	if (lim_q->cnt == 0)
	{
		exec->is_heredoc = FALSE;
	}
	else
	{
		ft_heredoc_sgh();
		exec->is_heredoc = TRUE;
		ft_ready_last_heredoc(lim_q);
		ft_pipe(exec->heredoc_fd);
		ft_heredoc_write_in_pipe(lim_q, exec, env_list);
		ft_default_signal();
		printf("heredoc(%d, %d)\n", exec->heredoc_fd[READ], exec->heredoc_fd[WRITE]);//
	}
}
