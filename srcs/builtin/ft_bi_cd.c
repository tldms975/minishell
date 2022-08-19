/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:03:46 by sielee            #+#    #+#             */
/*   Updated: 2022/08/20 01:38:18 by sielee           ###   ########seoul.kr  */
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

static int	ft_cd_to_path(t_envp_list *env, char *path)
{
	int		exit_status;
	char	*old_pwd;

	old_pwd = ft_get_env_value_ptr(env, "PWD");
	exit_status = chdir(path);
	if (exit_status == EXIT_SUCCESS)
	{
		ft_update_pwd(env, old_pwd);
	}
	else if (exit_status == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (exit_status);
}

static int	ft_cd_by_arg(t_envp_list *env, t_arg_node *dir)
{
	char	*path;

	path = dir->content;
	if (dir->next)
	{
		ft_putstr_fd("minishell: cd: Too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (ft_cd_to_path(env, path));
}

static int	ft_cd_by_env(t_envp_list *env, char *key)
{
	char	*path;

	path = ft_get_env_value_ptr(env, key);
	if (!path)
	{
		ft_putstr_fd("minishell cd: ", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putendl_fd(" not set", STDERR_FILENO);
		return (EXIT_NOTFOUND);
	}
	return (ft_cd_to_path(env, path));
}

int	ft_bi_cd(t_pipe_node *cmd)
{
	t_arg_node	*dir;

	dir = cmd->arg_list->front->next;
	if (!dir)
		return (ft_cd_by_env(cmd->env_list, "HOME"));
	else if (!(dir->next))
	{
		if (ft_strncmp(dir->content, "~", 2) == 0)
			return (ft_cd_by_env(cmd->env_list, "HOME"));
		if (ft_strncmp(dir->content, "-", 2) == 0)
			return (ft_cd_by_env(cmd->env_list, "OLDPWD"));
	}
	return (ft_cd_by_arg(cmd->env_list, dir));
}
