/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:50:42 by sielee            #+#    #+#             */
/*   Updated: 2022/08/10 23:27:43 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exe_parent_process(t_pipe_node *cmd, t_executor *exec)
{
	t_redir_node	*redir;

	redir = cmd->redir_list->front;
	while (redir)
	{
		ft_redirection(redir->type, redir->file_name, exec);
		redir = redir->next;
	}
	ft_dup2(exec->fd_read, STDIN_FILENO);
	ft_dup2(exec->fd_write, STDOUT_FILENO);
	return (ft_execute_built_in(cmd, exec->built_in_code));
}

void	ft_exe_child_process(t_pipe_node *cmd, t_executor *exec)
{
	t_redir_node	*redir;

	exec->cnt_child += 1;
	redir = cmd->redir_list->front;
	while (redir)
	{
		ft_redirection(redir->type, redir->file_name, exec);
		if (exec->fd_read < 0 || exec->fd_write < 0)
			exit(EXIT_NOTFOUND);//TODO: check
		redir = redir->next;
	}
	ft_dup2(exec->fd_read, STDIN_FILENO);
	ft_dup2(exec->fd_write, STDOUT_FILENO);
	if (exec->is_built_in)
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
