/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:38:06 by sielee            #+#    #+#             */
/*   Updated: 2022/08/18 19:32:26 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close_pipes(t_executor *exec)
{
	if (exec->is_heredoc)
	{
		if (exec->fd_read != exec->heredoc_fd[READ])
			ft_close(exec->fd_read);
		ft_close(exec->heredoc_fd[READ]);
	}
	else
	{
		ft_close(exec->fd_read);
		ft_close(exec->fd_write);
	}
}

static void	ft_set_pipe_fd(t_executor *exec, int cnt_pipe)
{
	if (exec->times == (cnt_pipe + 1))
		exec->l_pipe_fd_read = exec->r_pipe_fd[READ];
	else
	{
		if (exec->times != 1)
			exec->l_pipe_fd_read = exec->r_pipe_fd[READ];
		ft_pipe(exec->r_pipe_fd);
		if (exec->times == 1)
			exec->l_pipe_fd_read = exec->r_pipe_fd[READ];
	}
	if (exec->times % 2 == 1)
	{
		if (exec->times != (cnt_pipe + 1))
			exec->fd_write = exec->r_pipe_fd[WRITE];
		if (exec->times != 1)
			exec->fd_read = exec->l_pipe_fd_read;
	}
	else if (exec->times % 2 == 0)
	{
		exec->fd_read = exec->l_pipe_fd_read;
		if (exec->times != (cnt_pipe + 1))
			exec->fd_write = exec->r_pipe_fd[WRITE];
	}
	printf(">>[%d] pipe_line rdir<<\n", exec->times);//
	printf("basic(%d, ", exec->fd_read);//
	printf("%d)\n", exec->fd_write);//
}

static int	ft_ready_to_exec(t_pipe_node *cmd, t_executor *exec, \
t_envp_list *env, int cnt_pipe)
{
	exec->times += 1;
	exec->fd_read = STDIN_FILENO;
	exec->fd_write = STDOUT_FILENO;
	if (env->vec)
		ft_free_env_vec(env->vec);
	env->vec = ft_get_env_vector(env);
	cmd->env_list = env;
	ft_check_heredoc(cmd->lim_q, exec, env);
	exec->is_builtin = FALSE;
	exec->built_in_code = 0;
	if (!cmd->arg_list->front)
		exec->in = DO_NOT_EXE;
	else if (ft_check_builtin(cmd, exec) && (cnt_pipe == 0))
		exec->in = PARENT;
	else
	{
		exec->in = CHILD;
		ft_set_pipe_fd(exec, cnt_pipe);
	}
	return (ft_redirection(cmd->arg_list->front, cmd->redir_list->front, exec));
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
		ret = ft_ready_to_exec(pipe_line, &exec, env_list, pipe_list->cnt_pipe);
		if (exec.in == PARENT)
			return (ft_exe_in_parent_process(pipe_line, &exec));
		else if (exec.in == CHILD)
		{
			exec.pid = ft_fork_getting_last_pid(pipe_line, &exec);
			if (exec.pid == 0)
				ft_exe_in_child_process(pipe_line, &exec);
		}
		ft_close_pipes(&exec);
		pipe_line = pipe_line->next;
	}
	ret = ft_wait_all_child(exec.last_pid);
	return (ret);
}
