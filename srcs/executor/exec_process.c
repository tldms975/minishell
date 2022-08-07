/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:50:42 by sielee            #+#    #+#             */
/*   Updated: 2022/08/07 18:27:44 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exe_parent_process(t_pipe_line *cmd, t_executor *exec)
{
	while (cmd->redir)
	{
		ft_redirection(cmd->redir->type, cmd->redir->file_name, exec);
		cmd->redir = cmd->redir->next;
	}
	ft_dup2(exec->fd_read, STDIN_FILENO);
	ft_dup2(exec->fd_write, STDOUT_FILENO);
	ft_execute_built_in(cmd, exec->built_in_code);
	return (EXIT_SUCCESS);
}

void	ft_exe_child_process(t_pipe_line *cmd, t_executor *exec)
{
	exec->cnt_child += 1;
	while (cmd->redir)
	{
		ft_redirection(cmd->redir->type, cmd->redir->file_name, exec);
		if (exec->fd_read < 0 || exec->fd_write < 0)
			exit(EXIT_NOTFOUND);//TODO: check
		cmd->redir = cmd->redir->next;
	}
	ft_dup2(exec->fd_read, STDIN_FILENO);
	ft_dup2(exec->fd_write, STDOUT_FILENO);
	if (exec->is_built_in)
		ft_execute_built_in(cmd, exec->built_in_code);
	else
		ft_execute_cmd(cmd->arg, cmd->env->vec);
}

int	ft_get_exit_status(int status)
{
	const int	w_status = status & 0177;

	if (w_status == 0)
		return ((status >> 8) & 0x000000ff);
	if (w_status != 0177 && w_status != 0)
		return (w_status);
	return (0);
}

int	ft_wait_all_child(int pid, int n)
{
	int	stat;
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (i < n)
	{
		if (waitpid(-1, &stat, 0) == pid)
			ret = ft_get_exit_status(stat);
		i++;
	}
	return (ret);
}
