/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:50:42 by sielee            #+#    #+#             */
/*   Updated: 2022/08/18 02:26:46 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exe_in_parent_process(t_pipe_node *cmd, t_executor *exec)
{
	int	ret;
	int	old_fd_in;
	int	old_fd_out;

	old_fd_in = dup(STDIN_FILENO);
	old_fd_out = dup(STDOUT_FILENO);
	if (exec->fd_read != STDIN_FILENO)
		dup2(exec->fd_read, STDIN_FILENO);
	if (exec->fd_write != STDOUT_FILENO)
		dup2(exec->fd_write, STDOUT_FILENO);
	ret = ft_execute_built_in(cmd, exec->built_in_code);
	if (exec->fd_read != STDIN_FILENO)
		dup2(old_fd_in, STDIN_FILENO);
	if (exec->fd_write != STDOUT_FILENO)
		dup2(old_fd_out, STDOUT_FILENO);
	return (ret);
}

void	ft_exe_in_child_process(t_pipe_node *cmd, t_executor *exec)
{
	ft_dup2_for_child(exec->fd_read, STDIN_FILENO);
	ft_dup2_for_child(exec->fd_write, STDOUT_FILENO);
	if (exec->is_builtin)
		ft_execute_built_in(cmd, exec->built_in_code);
	else
		ft_execute_cmd(cmd->arg_list, cmd->env_list);
}

int	ft_get_child_exit_status(int status)
{
	const int	w_status = status & 0177;

	if (w_status == 0)
		return ((status >> 8) & 0x000000ff);
	if (w_status != 0177 && w_status != 0)
		return (w_status);
	return (0);
}

int	ft_wait_all_child(int last_pid)
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
		if (wait_ret == last_pid)
			ret = stat;
	}
	return (ft_get_child_exit_status(ret));
}
