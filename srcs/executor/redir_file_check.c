/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:34:43 by sielee            #+#    #+#             */
/*   Updated: 2022/08/16 17:31:11 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_errmsg_by_notfound(char *file_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file_name, STDERR_FILENO);
	ft_perror("");
}

static void	ft_print_errmsg_by_ifdir(t_arg_node *arg, char *file_name, \
t_token_type type)
{
	if ((type == REDIR_OUT) || (type == REDIR_APPEND))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file_name, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(arg->content, STDERR_FILENO);
		ft_putstr_fd(": (standard input)", STDERR_FILENO);
	}
	ft_perror("");
}

static void	ft_print_errmsg_no_permission(t_arg_node *arg, char *file_name)
{
	ft_putstr_fd(arg->content, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(file_name, STDERR_FILENO);
	ft_perror("");
}

int	ft_check_valid_redir_files(t_arg_node *arg, t_redir_node *redir)
{
	t_stat	stat;

	if (redir->type != REDIR_HEREDOC)
	{
		if (lstat(redir->file_name, &stat) == -1)
			ft_print_errmsg_by_notfound(redir->file_name);
		else if ((stat.st_mode & S_IFDIR) && arg)
			ft_print_errmsg_by_ifdir(arg, redir->file_name, redir->type);
		else if ((stat.st_mode & S_IFDIR) && !arg)
			return (-1);
		else if (!(stat.st_mode & S_IXUSR))
			ft_print_errmsg_no_permission(arg, redir->file_name);
		else
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}