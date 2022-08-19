/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:34:43 by sielee            #+#    #+#             */
/*   Updated: 2022/08/20 02:07:09 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_errmsg_unexecutable(char *file_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file_name, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}

static void	ft_print_errmsg_by_isdir(t_arg_node *arg, char *file_name, \
t_token_type type)
{
	if ((type == REDIR_OUT) || (type == REDIR_APPEND))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file_name, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
	}
	else if (arg)
	{
		ft_putstr_fd(arg->content, STDERR_FILENO);
		ft_putstr_fd(": (standard input)", STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
	}
}

void	ft_print_errmsg_no_permission(char *file_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file_name, STDERR_FILENO);
	ft_putendl_fd(": Permission denied", STDERR_FILENO);
}

static void	ft_print_errmsg_ambigious(t_executor *exec)
{
	exec->in = DO_NOT_EXE;
	ft_putstr_fd("minishell", STDERR_FILENO);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
}

int	ft_check_valid_redir_files(t_arg_node *arg, t_redir_node *redir, \
t_executor *exec)
{
	int		lstat_ret;
	t_stat	stat;

	if (!redir->file_name)
	{
		ft_print_errmsg_ambigious(exec);
		return (EXIT_FAILURE);
	}
	else
	{
		lstat_ret = lstat(redir->file_name, &stat);
		if (lstat_ret == -1 && (redir->type == REDIR_IN))
			ft_print_errmsg_unexecutable(redir->file_name);
		else if ((lstat_ret != -1) && (stat.st_mode & S_IFDIR))
			ft_print_errmsg_by_isdir(arg, redir->file_name, redir->type);
		else if ((lstat_ret != -1) && ((((redir->type == REDIR_IN) \
		&& !(stat.st_mode & S_IRUSR))) || ((redir->type == REDIR_OUT) \
		&& !((stat.st_mode & S_IRUSR) && (stat.st_mode & S_IWUSR)))))
			ft_print_errmsg_no_permission(redir->file_name);
		else
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
}
