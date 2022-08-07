/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:51 by sielee            #+#    #+#             */
/*   Updated: 2022/08/07 20:57:36 by sielee           ###   ########seoul.kr  */
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

static void	ft_ready_to_exec(t_pipe_node *cmd, t_executor	*exec, t_envp_list *env)
{
	exec->fd_read = STDIN_FILENO;
	exec->fd_write = STDOUT_FILENO;
	exec->pipe_fd[READ] = STDIN_FILENO;
	exec->pipe_fd[WRITE] = STDOUT_FILENO;
	exec->is_built_in = 0;
	exec->built_in_code = 0;
	cmd->env_list = env;
}

int	ft_execute(t_pipe_list *pipe_list, t_envp_list *env_list)
{
	t_pipe_node	*pipe_line;
	t_executor	exec;
	int			ret;

	exec.cnt_child = 0;
	pipe_line = pipe_list->head;
	while (pipe_line)
	{
		ft_ready_to_exec(pipe_line, &exec, env_list);
		ft_check_heredoc(pipe_line->lim_q, &exec);
		if (!ft_check_builtin(pipe_line, &exec) || pipe_list->cnt_pipe)
		{
			ft_pipe(exec.pipe_fd);
			exec.pid = ft_fork();
			if (exec.pid == 0)
				ft_exe_child_process(pipe_line, exec);
		}
		else
			return (ft_exe_parent_process(pipe_line, exec));
		pipe_line = pipe_line->next;
	}
	ret = ft_wait_all_child(exec.pid, exec.cnt_child);
	return (ret);
}
