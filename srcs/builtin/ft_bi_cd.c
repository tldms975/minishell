/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:28 by sielee            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/07 22:10:54 by sielee           ###   ########seoul.kr  */
=======
/*   Updated: 2022/08/07 21:21:22 by sielee           ###   ########seoul.kr  */
>>>>>>> ff292cba4812a7e9f1fd65bf75af118e556cb79c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_pwd(t_envp_list *env, const char *oldpwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_perror("getcwd error");
		ft_exit(EXIT_FAILURE);
	}
	ft_mod_env_value(env, "OLDPWD", oldpwd);
	ft_mod_env_value(env, "PWD", pwd);
	ft_free((void **) &pwd);
}

static int	ft_cd_to_arg(t_envp_list *env, const char *dir)
{
	int		ret;
	char	*old_pwd;

	old_pwd = ft_get_env_value(env, "PWD");
	ret = chdir(dir);
	if (ret == EXIT_SUCCESS)
	{
		ft_update_pwd(env, old_pwd);
	}
	else if (ret == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_perror(dir);
	}
	return (ret);
}

static int	ft_cd_by_env(t_envp_list *env, const char *key)
{
	char	*path;

	path = ft_get_env_value(env, key);
	if (!path)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putendl_fd(" not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_cd_to_arg(env, path);
}

int	ft_bi_cd(t_pipe_node *cmd)
{
	t_arg_node	*dir;

	dir = cmd->arg_list->front->next;
	if (!dir)
		return (ft_cd_by_env(cmd->env_list, "HOME"));
	else
	{
		if (ft_strncmp(dir->content, "~", 2))
			return (ft_cd_by_env(cmd->env_list, "HOME"));
		if (ft_strncmp(dir->content, "-", 2))
			return (ft_cd_by_env(cmd->env_list, "OLDPWD"));
	}
	return (ft_cd_to_arg(cmd->env_list, dir->content));
}
