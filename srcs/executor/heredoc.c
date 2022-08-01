/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:55:39 by sielee            #+#    #+#             */
/*   Updated: 2022/08/01 19:49:29 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_heredoc(t_executor *exec, char *limiter)
{
	char	*line;

	line = NULL;
	while (ft_strncmp(line, limiter, (ft_strlen(limiter) + 1)) != 0)
	{
		line = readline("> ");
		if (!line)
			break ;
		line = ft_strjoin(line, "\n");
		write(exec->fd_write, line, ft_strlen(line));
		free(line);
	}
}

void	ft_heredoc(t_limiter_q	*lim_q, t_executor *exec)
{
	while (!ft_is_empty_q(lim_q))
	{
		ft_read_heredoc(exec, lim_q->front->data);
		close(exec->fd_write);
		ft_pipe(exec->heredoc_fd);
		close(exec->heredoc_fd[READ]);//부모에서는 닫아주는게 맞다
		exec->fd_write = exec->heredoc_fd[WRITE];
		ft_dequeue(lim_q);
	}
	exec->fd_read = exec->heredoc_fd[READ];
}

void	ft_check_heredoc(t_cmd_tree *cmd_tree, t_executor *exec)
{
	int	i;

	i = 0;
	if (i < cmd_tree->cnt_heredoc)
	{
		ft_pipe(exec->heredoc_fd);
		close(exec->heredoc_fd[READ]);//부모에서는 닫아주는게 맞다
		exec->fd_write = exec->heredoc_fd[WRITE];
		ft_heredoc(cmd_tree->lim_q, exec);
		i++;
	}
}
