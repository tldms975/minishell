/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:35:18 by sielee            #+#    #+#             */
/*   Updated: 2022/08/19 00:49:23 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_errmsg_unexecutable(char *file_name, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file_name, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	ft_check_cmd_path(char *arg, char *cmd, char *msg)
{
	t_stat	stat;
	int		lst_ret;

	lst_ret = lstat(cmd, &stat);
	if (lst_ret == -1)
	{
		ft_print_errmsg_unexecutable(arg, msg);
		exit (EXIT_NOTFOUND);
	}
	if (stat.st_mode & S_IFDIR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": is a directory", STDERR_FILENO);
		exit (EXIT_UNEXECUTABLE);
	}
	if (!(stat.st_mode & S_IXUSR))
	{
		ft_print_errmsg_no_permission(arg);
		exit (EXIT_UNEXECUTABLE);
	}
}
