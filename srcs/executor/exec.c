/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:51 by sielee            #+#    #+#             */
/*   Updated: 2022/08/04 02:29:35 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_cmd(t_arg_list *arg, char *envp[])
{
	char	**cmd_vec;
	char	*cmd_path;

	execve(cmd_path, cmd_vec, envp);
	ft_perror("execute error");
	//exit();
}

static void	ft_init_exec(t_executor	*exec, char *envp[])
{
	exec->fd_read = STDIN_FILENO;
	exec->fd_write = STDOUT_FILENO;
	exec->pipe_fd[READ] = STDIN_FILENO;
	exec->pipe_fd[WRITE] = STDOUT_FILENO;
	exec->is_built_in = 0;
	exec->built_in_code = -1;
}

int	ft_execute(t_pipe_head *pipe_head, char *envp[])
{
	t_pipe_line	*pipe_line;
	t_executor	*exec;
	int			ret;

	exec->cnt_child = 0;
	pipe_line = pipe_head->head;
	while (pipe_line)
	{
		ft_init_exec(exec, envp);
		ft_check_heredoc(pipe_line->cmd->lim_q, exec);
		if (!ft_check_builtin(pipe_line->cmd, exec) || pipe_head->cnt_pipe)
		{
			ft_pipe(exec->pipe_fd);
			exec->pid = ft_fork();
			if (exec->pid == 0)
				ft_exe_child_process(pipe_line->cmd, exec, envp);
			else
				pipe_line = pipe_line->next_pipe;
		}
		else
			return (ft_exe_parent_process(pipe_line->cmd, exec));
	}
	ret = ft_wait_all_child(exec->pid, exec->cnt_child);
	return (ret);
}
