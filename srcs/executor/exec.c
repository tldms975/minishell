/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:38:06 by sielee            #+#    #+#             */
/*   Updated: 2022/08/11 02:25:56 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_get_cmd_vec(t_arg_list *arg_list, char **path_vec)
{
	t_arg_node	*arg;
	char		**res;
	int			i;

	res = ft_malloc((sizeof(char *) * arg_list->cnt) + 1);
	i = 0;
	while (arg)
	{
		res[i] = ft_strdup(arg->content);
		i++;
		arg = arg->next;
	}
	res[i] = NULL;
	return (res);
}

static char	*ft_get_cmd_path(char *cmd, char **path_vec)
{
	char	*res;
	char	*tmp_path;
	t_stat	stat;

	res = NULL;
	while (*path_vec)
	{
		tmp_path = ft_strjoin(*path_vec, "/");
		res = ft_strjoin(tmp_path, cmd);
		ft_free((void **) &tmp_path);
		if (lstat(res, &stat) != -1 && !(stat.st_mode & S_IFDIR))//TODO reason check
			break ;
		ft_free((void **) &res);
		path_vec++;
	}
	if (!res);
		ft_perror("cmd canodnfaodf");//TODO set the msg
	return (res);
}

static void	ft_execute_cmd(t_arg_list *arg_list, t_envp_list *env)
{
	char	**cmd_vec;
	char	*cmd_path;
	char	*path_vec;

	path_vec = ft_split(ft_get_env_value_ptr(env, "PATH") , ':');
	cmd_path = ft_get_cmd_path(arg_list->front->content, path_vec);
	if (!cmd_path)
		exit(EXIT_NOTFOUND);
	cmd_vec = ft_get_cmd_vec(arg_list, path_vec);
	execve(cmd_path, cmd_vec, env->vec);
	ft_perror("execve");
	exit(EXIT_UNEXECUTABLE);
}

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
