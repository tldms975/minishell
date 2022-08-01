/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:51 by sielee            #+#    #+#             */
/*   Updated: 2022/08/01 15:44:14 by sielee           ###   ########seoul.kr  */
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

	execve(,envp);
}

void	ft_redirection(t_executor *exec)
{
	if (REDIR_IN && heredoc보다 뒤에 있음)
	{
		exec->fd_read = ft_open(, O_RDONLY);
	}
	else if (REDIR_OUT)
	{
		exec->fd_write = ft_open(, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (REDIR_APPEND)
	{
		exec->fd_write = ft_open(, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
}

void	ft_child_process(t_lexer *cmd_tree, t_executor *exec)
{
	
	ft_redirection(exec);
	ft_dup2(exec->fd_read, STDIN_FILENO);
	close(exec->fd_read);
	ft_dup2(exec->fd_write, STDOUT_FILENO);
	close(exec->fd_write);
	ft_execute_cmd(/*실행가능단위*/);
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
		line = readline(">");
		if (!line)
			break ;
		write(exec->fd_write, line, ft_strlen(line));
		free(line);
	}
}

void	ft_heredoc(t_ *cmd_tree, t_executor *exec)
{
	t_limiter_q	*lim_q;

	lim_q = cmd_tree->lim_q;
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

void	ft_check_heredoc(t_ *cmd_tree, t_executor *exec)
{
	int	i;

	i = 0;
	if (i < cmd_tree->cnt_heredoc)
	{
		ft_pipe(exec->heredoc_fd);
		close(exec->heredoc_fd[READ]);//부모에서는 닫아주는게 맞다
		exec->fd_write = exec->heredoc_fd[WRITE];
		ft_heredoc();
		i++;
	}
}

int	ft_execute(t_ *cmd_tree, char *envp[])
{
	t_executor	*exec;
	int			ret;
	int			i;

	ft_check_heredoc(cmd_tree, exec);
	i = 0;
	while (i <= cmd_tree->cnt_pipe)
	{
		// 파이프 기준으로 순서대로 i번째 명령씩을 제공
		if (i != 0)
			ft_pipe(exec->pipe_fd);
		exec->pid = ft_fork();
		if (exec->pid == 0)
			ft_child_process(cmd_tree, exec, envp);
		i++;
	}
	ret = ft_wait_all(exec->pid, cmd_tree->cnt_pipe);
	return (ret);
}
