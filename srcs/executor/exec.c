/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:38:06 by sielee            #+#    #+#             */
/*   Updated: 2022/08/13 17:44:49 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_ready_to_exec(t_pipe_node *cmd, t_executor *exec, \
t_envp_list *env)
{
	exec->fd_read = STDIN_FILENO;
	exec->fd_write = STDOUT_FILENO;
	exec->pipe_fd[READ] = STDIN_FILENO;
	exec->pipe_fd[WRITE] = STDOUT_FILENO;
	exec->is_built_in = 0;
	exec->built_in_code = 0;
	cmd->env_list = env;
	if (env->vec)
		ft_free((void **) &env->vec);
	env->vec = ft_get_env_vector(env);
}

int	ft_execute(t_pipe_list *pipe_list, t_envp_list *env_list)
{
	t_pipe_node	*pipe_line;
	t_executor	exec;
	int			ret;

	pipe_line = pipe_list->head;
	while (pipe_line)
	{
		ft_ready_to_exec(pipe_line, &exec, env_list);
		ft_check_heredoc(pipe_line->lim_q, &exec);
		if (!ft_check_builtin(pipe_line, &exec) || !pipe_list->cnt_pipe)
		{
			ft_pipe(exec.pipe_fd);
			exec.pid = ft_fork();
			if (exec.pid == 0)
				ft_exe_child_process(pipe_line, &exec);
		}
		else
			return (ft_exe_parent_process(pipe_line, &exec));
		ret = ft_wait_all_child(exec.pid);
		pipe_line = pipe_line->next;
	}
	return (ret);
}
