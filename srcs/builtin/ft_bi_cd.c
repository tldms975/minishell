/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:28 by sielee            #+#    #+#             */
/*   Updated: 2022/08/06 02:27:57 by sielee           ###   ########seoul.kr  */
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
	ft_update_env(env, "OLDPWD", oldpwd);
	ft_update_env(env, "PWD", pwd);
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

int	ft_bi_cd(t_cmd *cmd, t_envp_list *env)
{
	t_arg_list	*dir;

	dir = cmd->arg->next;
	if (!dir)
		return (ft_cd_by_env(env, "HOME"));
	else
	{
		if (ft_strncmp(dir->content, "~", 2))
			return (ft_cd_by_env(env, "HOME"));
		if (ft_strncmp(dir->content, "-", 2))
			return (ft_cd_by_env(env, "OLDPWD"));
	}
	return (ft_cd_to_arg(env, dir->content));
}
