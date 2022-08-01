/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:51 by sielee            #+#    #+#             */
/*   Updated: 2022/08/01 22:47:41 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_cmd(char *envp[])
{
	//path찾기
	char	*cmd_line;

	execve(,envp);
}

void	ft_redirection(t_executor *exec)
{
	if (REDIR_IN && heredoc보다 뒤에 있음)
	{
		exec->fd_read = ft_open(infile_name, O_RDONLY);
	}
	else if (REDIR_OUT)
	{
		exec->fd_write = ft_open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC);
	}
	else if (REDIR_APPEND)
	{
		exec->fd_write = ft_open(outfile_name, O_WRONLY | O_CREAT | O_APPEND);
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
		// 파이프라인 단위로 들어오
		if (i != 0)
			ft_pipe(exec->pipe_fd);
		exec->pid = ft_fork();
		if (exec->pid == 0)
			ft_child_process(cmd_tree->pipeline, exec, envp);
		i++;
	}
	ret = ft_wait_all(exec->pid, cmd_tree->cnt_pipe);
	return (ret);
}
