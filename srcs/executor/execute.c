/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:51 by sielee            #+#    #+#             */
/*   Updated: 2022/07/30 22:54:44 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_exit_status(int status)
{
	const int	w_status = status & 0177;

	if (w_status == 0)
		return ((status >> 8) & 0x000000ff);
	if (w_status != 0177 && w_status != 0)
		return (w_status);
	return (0);
}

void	ft_execute_cmd()
{
	//path찾기
	char	*cmd_line;

	while ()//P일때까지
	//execve(,, envp);
}

void	ft_redirection()
{
	if (REDIR_IN)
	{
		fd_read = ft_open(, O_RDONLY);
	}
	else if (REDIR_OUT)
	{
		fd_write = ft_open(, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (REDIR_APPEND)
	{
		fd_write = ft_open(, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
}

void	ft_child_process(t_lexer *cmd_tree, t_executor *exec)
{
	ft_redirection();
	ft_dup2(ag->fd_read, STDIN_FILENO);
	close(exec->fd_read);
	ft_dup2(exec->fd_write, STDOUT_FILENO);
	close(exec->fd_write);
	ft_execute_cmd();
}

int	ft_wait_all(int pid, int n)
{
	int	stat;
	int	ret;
	int	i;

	ret = -1;
	i = 1;
	while (i < n)
	{
		if (waitpid(-1, &stat, 0) == pid)
			ret = ft_get_exit_status(stat);
		i++;
	}
	return (ret);
}

void	ft_read_heredoc(t_executor *exec, char *limiter)
{
	char	*line;

	while (ft_strncmp(line, limiter, (ft_strlen(limiter) + 1)) != 0)
	{
		write(fd_write, line, ft_strlen(line));
		free(line);
	}
}

void	ft_heredoc(t_lexer *cmd_tree, t_executor *exec)
{
	t_limiter_q	*lim_q;

	exec->fd_read = exec->heredoc_fd[READ];
	exec->fd_write = exec->heredoc_fd[WRITE];
	lim_q = /*q들어있는 구조체에서 가져오기*/;
	while (!ft_is_empty_q(lim_q))
	{
		ft_read_heredoc(, lim_q->front->data);
		ft_pipe(exec_info->heredoc_fd);
		ft_dequeue(limiter);
	}
}

void	ft_check_heredoc(t_lexer *cmd_tree, t_executor *exec)
{
	if (cmd_tree->cnt_heredoc > 0)
	{
		ft_pipe(exec_info->heredoc_fd)
		ft_heredoc();
	}
}

int	ft_executor(t_lexer *cmd_tree, char *envp[])
{
	t_executor	*exec;
	int			ret;
	int			i;

	ft_check_heredoc(cmd_tree, exec, envp);
	i = 0;
	while (i <= cmd_tree->cnt_pipe)
	{
		if (i != 0)
			ft_pipe(exec_info->pipe_fd);
		exec->pid = ft_fork();
		if (exec->pid == 0)
			ft_child_process(cmd_tree, exec, envp);
		i++;
	}
	ret = ft_wait_all(last_pid, cnt_pipe);
	return (ret);
}
