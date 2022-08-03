/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:51 by sielee            #+#    #+#             */
/*   Updated: 2022/08/03 21:28:11 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cmd_path(char *cmd, char **envp)
{
	char	**split_path;
	char	*piece_of_path;
	char	*cmd_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	split_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (split_path[i])
	{
		piece_of_path = ft_strjoin(split_path[i], "/");
		cmd_path = ft_strjoin(piece_of_path, cmd);
		free(piece_of_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (0);
}

void	ft_execute_cmd(t_arg_list *arg, char *envp[])
{
	char	**cmd_vec;
	char	*cmd_path;

	while (arg)
	{
		cmd_vec
	}
	execve(cmd_path, cmd_vec, envp);
	ft_perror("execute error");
	//exit();
}

void	ft_init_exec(t_executor	*exec, char *envp[])
{
	exec->fd_read = STDIN_FILENO;
	exec->fd_write = STDOUT_FILENO;
	exec->pipe_fd[READ] = STDIN_FILENO;
	exec->pipe_fd[WRITE] = STDOUT_FILENO;
	exec->builtin_code = 0;
	//TODO: envp list구현
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
		if (!ft_exe_parent_process(pipe_line->cmd, exec, pipe_head->cnt_pipe)) //TODO:builtin 구현하고 다시 짜기
		{
			ft_pipe(exec->pipe_fd);
			exec->pid = ft_fork();
			if (exec->pid == 0)
				ft_exe_child_process(pipe_line->cmd, exec, envp);
			else
				pipe_line = pipe_line->next_pipe;
		}
		else
			break ;
	}
	ret = ft_wait_all(exec->pid, exec->cnt_child);
	return (ret);
}
