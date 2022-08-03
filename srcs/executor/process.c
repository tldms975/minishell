/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:50:42 by sielee            #+#    #+#             */
/*   Updated: 2022/08/03 19:11:41 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exe_parent_process(t_cmd *cmd, t_executor *exec)
{
	int			i;
	const char	*builtin_arr[7] = {"echo", ""};

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmd->arg->content, builtin_arr[i], (ft_strlen(builtin_arr[i]) + 1)))
		{
			ft_redirection(cmd->redir->redir_type, cmd->redir->file_name, exec);
			ft_dup2(exec->fd_read, STDIN_FILENO);
			ft_dup2(exec->fd_write, STDOUT_FILENO);
			ft_do_builtin(cmd, exec, );
			return (1);
		}
		i++;
	}
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
