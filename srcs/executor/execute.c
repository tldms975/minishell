/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:51 by sielee            #+#    #+#             */
/*   Updated: 2022/08/02 21:18:38 by sielee           ###   ########seoul.kr  */
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
		cmd_vec;
	}
	if (execve(cmd_path, cmd_vec, envp) == -1)
		ft_perror("execute error");
}

void	ft_child_process(t_cmd *cmd, t_executor *exec, char *envp[])
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

void	ft_init_fd(t_executor	*exec)
{
	exec->fd_read = STDIN_FILENO;
	exec->fd_write = STDOUT_FILENO;
}

int	ft_execute(t_pipe_head *pipe_head, char *envp[])
{
	t_pipe_line	*pipe_line;
	t_executor	*exec;
	int			ret;

	pipe_line = pipe_head->head;
	while (pipe_line)
	{
		ft_init_fd(exec);
		ft_check_heredoc(pipe_line->cmd->lim_q, exec);
		if (pipe_head->cnt_pipe > 1)
			ft_pipe(exec->pipe_fd);
		exec->pid = ft_fork();
		if (exec->pid == 0)
		{
			ft_child_process(pipe_line->cmd, exec, envp);
		}
		else
		{
			pipe_line = pipe_line->next_pipe;
		}
	}
	ret = ft_wait_all(exec->pid, pipe_head->cnt_pipe);
	return (ret);
}
