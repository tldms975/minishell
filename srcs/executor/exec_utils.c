/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 02:29:44 by sielee            #+#    #+#             */
/*   Updated: 2022/08/19 22:38:20 by sielee           ###   ########seoul.kr  */
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

static char	*ft_get_cmd_path(char *cmd, t_envp_list *env)
{
	char	*res;
	char	*tmp_path;
	char	**path_vec;
	t_stat	stat;

	res = NULL;
	path_vec = ft_split(ft_get_env_value_ptr(env, "PATH"), ':');
	if (!path_vec || \
	ft_strncmp((ft_get_env_value_ptr(env, "PATH")), "", 1) == 0)
	{
		cmd = ft_strjoin("./", cmd);
		return (cmd);
	}
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
	return (res);
}

void	ft_execute_cmd(t_arg_list *arg_list, t_envp_list *env)
{
	char	*cmd_path;
	char	**cmd_vec;

	if (ft_strchr(arg_list->front->content, '/'))
	{
		cmd_path = arg_list->front->content;
		ft_check_cmd_path(arg_list->front->content, cmd_path, \
		": No such file or directory");
	}
	else
	{
		cmd_path = ft_get_cmd_path(arg_list->front->content, env);
		ft_check_cmd_path(arg_list->front->content, cmd_path, \
		": command not found");
	}
	cmd_vec = ft_get_cmd_vec(arg_list);
	execve(cmd_path, cmd_vec, env->vec);
}
