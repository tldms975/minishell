/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:51 by sielee            #+#    #+#             */
/*   Updated: 2022/07/30 00:42:09 by sielee           ###   ########seoul.kr  */
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

	while ()//리다이렉션 만날 때까지

	//execve(,, envp);
}

void	ft_redirection()
{
	if ("<")
	{
		fd_read = ft_open(, O_RDONLY);
	}
	else if (">")
	{
		fd_write = ft_open(, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (">>")
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

int	ft_wait(int pid, int cnt_child)
{
	int	stat;
	int	ret;
	int	i;

	ret = -1;
	i = 1;
	while (i < cnt_child)
	{
		if (waitpid(-1, &stat, 0) == pid)
			ret = ft_get_exit_status(stat);
		i++;
	}
	return (ret);
}

void	ft_heredoc(t_lexer *cmd_tree, t_executor *exec_info)
{
	
}

void	ft_init_executor(t_lexer *cmd_tree, t_executor *exec_info)
{
	if (cmd_tree->cnt_pipe > 0)
		ft_pipe(exec_info->pipe_fd);
	if (cmd_tree->cnt_heredoc > 0)
	{
		ft_pipe(exec_info->heredoc_fd)
		ft_heredoc();
	}
}

int	ft_executor(t_lexer *cmd_tree, char *envp[])
{
	t_executor	*exec_info;
	int			ret;
	int			i;

	ft_init_executor(cmd_tree, exec_info, envp);
	i = 0;
	while (i <= cmd_tree->cnt_pipe)
	{
		pid = fork();
		if (pid == -1)
			ft_error("fork failed");
		else if (pid == 0)
			ft_child_process(cmd_tree, exec_info, envp);
		i++;
	}
	ret = ft_wait(last_pid, cnt_pipe);
	return (ret);
}

