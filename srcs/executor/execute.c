/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:51 by sielee            #+#    #+#             */
/*   Updated: 2022/08/01 18:00:43 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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



int	ft_execute(t_ *cmd_tree, char *envp[])
{
	t_executor	*exec;
	int			ret;
	int			i;

	i = 0;
	while (i <= cmd_tree->cnt_pipe)
	{
		ft_check_heredoc(cmd_tree, exec);
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
