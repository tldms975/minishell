/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:50:42 by sielee            #+#    #+#             */
/*   Updated: 2022/08/15 20:27:12 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exe_in_parent_process(t_pipe_node *cmd, t_executor *exec)
{
	ft_redirection(cmd->redir_list->front, exec);
	ft_dup2(exec->fd_read, STDIN_FILENO);
	ft_dup2(exec->fd_write, STDOUT_FILENO);
	return (ft_execute_built_in(cmd, exec->built_in_code));
}

void	ft_exe_in_child_process(t_pipe_node *cmd, t_executor *exec)
{
	ft_redirection(cmd->redir_list->front, exec);
	ft_dup2(exec->fd_read, STDIN_FILENO);
	ft_dup2(exec->fd_write, STDOUT_FILENO);
	if (exec->is_builtin)
		ft_execute_built_in(cmd, exec->built_in_code);
	else
		ft_execute_cmd(cmd->arg_list, cmd->env_list);
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

int	ft_wait_all_child(int pid)
{
	int	stat;
	int	wait_ret;
	int	ret;

	ret = EXIT_FAILURE;
	while (1)
	{
		wait_ret = waitpid(-1, &stat, 0);
		if (wait_ret < 0)
			break ;
		if (wait_ret == pid)
			ret = ft_get_exit_status(stat);
	}
	return (ret);
}
