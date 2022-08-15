/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 02:29:44 by sielee            #+#    #+#             */
/*   Updated: 2022/08/15 16:10:15 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_get_cmd_vec(t_arg_list *arg_list)
{
	t_arg_node	*arg;
	char		**res;
	int			i;

	res = ft_malloc((sizeof(char *) * (arg_list->cnt + 1)));
	i = 0;
	arg = arg_list->front;
	while (arg)
	{
		res[i] = ft_strdup(arg->content);
		i++;
		arg = arg->next;
	}
	res[i] = NULL;
	return (res);
}

void	ft_exit_by_wrong_cmd(char *arg, char *msg, int stat)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(stat);
}

static char	*ft_get_cmd_path(char *cmd, t_envp_list *env)
{
	char	*res;
	char	*tmp_path;
	char	**path_vec;
	t_stat	stat;

	res = NULL;
	path_vec = ft_split(ft_get_env_value_ptr(env, "PATH"), ':');
	if (!path_vec)
		return (NULL);
	while (*path_vec)
	{
		tmp_path = ft_strjoin(*path_vec, "/");
		res = ft_strjoin(tmp_path, cmd);
		ft_free((void **)&tmp_path);
		if (lstat(res, &stat) != -1 && !(stat.st_mode & S_IFDIR))
			break ;
		ft_free((void **) &res);
		path_vec++;
	}
	if (!res)
		ft_exit_by_wrong_cmd(cmd, "command not found", EXIT_NOTFOUND);
	return (res);
}

void	ft_execute_cmd(t_arg_list *arg_list, t_envp_list *env)
{
	char	*cmd_path;
	char	**cmd_vec;

	cmd_path = ft_get_cmd_path(arg_list->front->content, env);
	cmd_vec = ft_get_cmd_vec(arg_list);
	execve(cmd_path, cmd_vec, env->vec);
	ft_perror("execve");
	exit(EXIT_UNEXECUTABLE);
}
