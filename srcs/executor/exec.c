/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:38:06 by sielee            #+#    #+#             */
/*   Updated: 2022/08/15 16:55:21 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_fd(t_executor *exec, int cnt_pipe)
{
	exec->fd_read = STDIN_FILENO;
	exec->fd_write = STDOUT_FILENO;
	if ((exec->times % 2 == 1) && (exec->times <= cnt_pipe))
	{
		if (exec->times != 1)
			exec->l_pipe_fd_read = exec->r_pipe_fd[READ];
		ft_pipe(exec->r_pipe_fd);
		if (exec->times == 1)
			exec->l_pipe_fd_read = exec->r_pipe_fd[READ];
	}
	if (exec->times % 2 == 1)
	{
		exec->fd_write = exec->r_pipe_fd[WRITE];
		if (exec->times != 1)
			exec->fd_read = exec->l_pipe_fd_read;
	}
	if (exec->times % 2 == 0)
	{
		exec->fd_read = exec->l_pipe_fd_read;
		if (exec->times != (cnt_pipe + 1))
			exec->fd_write = exec->r_pipe_fd[WRITE];
	}
}

static void	ft_ready_to_exec(t_pipe_node *cmd, t_executor *exec, \
t_envp_list *env, int cnt_pipe)
{
	exec->times += 1;
	if (env->vec)
		ft_free((void **) &env->vec);
	env->vec = ft_get_env_vector(env);
	cmd->env_list = env;
	exec->is_heredoc = FALSE;
	exec->is_builtin = FALSE;
	exec->built_in_code = 0;
	if (!cnt_pipe && ft_check_builtin(cmd, exec))
		exec->in = PARENT;
	else
	{
		exec->in = CHILD;
		ft_set_fd(exec, cnt_pipe);
	}
}

int	ft_execute(t_pipe_list *pipe_list, t_envp_list *env_list)
{
	t_pipe_node	*pipe_line;
	t_executor	exec;
	int			ret;

	exec.times = 0;
	pipe_line = pipe_list->head;
	while (pipe_line)
	{
		ft_ready_to_exec(pipe_line, &exec, env_list, pipe_list->cnt_pipe);
		ft_check_heredoc(pipe_line->lim_q, &exec);
		if (exec.in == PARENT)
			return (ft_exe_in_parent_process(pipe_line, &exec));
		else
		{
			exec.pid = ft_fork();
			if (exec.pid == 0)
				ft_exe_in_child_process(pipe_line, &exec);
			ft_close(exec.fd_read);
			ft_close(exec.fd_write);
		}
		ret = ft_wait_all_child(exec.pid);
		pipe_line = pipe_line->next;
	}
	return (ret);
}
