/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:50:42 by sielee            #+#    #+#             */
/*   Updated: 2022/08/03 21:23:25 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exe_parent_process(t_cmd *cmd, t_executor *exec, int cnt_pipe)
{
	if (cnt_pipe == 1 && ft_is_builtin(cmd, exec))
	{
		while (cmd->redir)
		{
			ft_redirection(cmd->redir->redir_type, cmd->redir->file_name, exec);
			cmd->redir = cmd->redir->next;
		}
		ft_dup2(exec->fd_read, STDIN_FILENO);
		ft_dup2(exec->fd_write, STDOUT_FILENO);
		ft_run_builtin(cmd, exec, exec->builtin_code);
		return (1);
	}
	else
		return (0);
}

void	ft_exe_child_process(t_cmd *cmd, t_executor *exec, char *envp[])
{
	while (cmd->redir)
	{
		ft_redirection(cmd->redir->redir_type, cmd->redir->file_name, exec);
		if (exec->fd_read < 0 || exec->fd_write < 0)
			exit(127);//TODO: check
		cmd->redir = cmd->redir->next;
	}
	ft_dup2(exec->fd_read, STDIN_FILENO);
	ft_dup2(exec->fd_write, STDOUT_FILENO);
	exec->cnt_child += 1;
	ft_execute_cmd(cmd->arg, envp);
}

static int	ft_get_exit_status(int status)
{
	const int	w_status = status & 0177;

	if (w_status == 0)
		return ((status >> 8) & 0x000000ff);
	if (w_status != 0177 && w_status != 0)
		return (w_status);
	return (0);
}

int	ft_wait_all(int pid, int n)
{
	int	stat;
	int	ret;
	int	i;

	ret = -1;
	i = 0;
	while (i < n)
	{
		if (waitpid(-1, &stat, 0) == pid)
			ret = ft_get_exit_status(stat);
		i++;
	}
	return (ret);
}
