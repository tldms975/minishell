/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:33 by sielee            #+#    #+#             */
/*   Updated: 2022/08/15 15:57:14 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumeric(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static void	ft_exit_with_errmsg_numeric(char *str)
{
	ft_print_exit();
	ft_putstr_fd("bash: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(EXIT_OVER);
}

static int	ft_exit_fail_too_many_args(void)
{
	ft_print_exit();
	ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	ft_bi_exit(t_pipe_node *cmd)
{
	t_arg_node	*bi_arg;

	bi_arg = cmd->arg_list->front->next;
	if (!bi_arg)
	{
		ft_exit(EXIT_SUCCESS);
	}
	else if (ft_isnumeric(bi_arg->content))
	{
		if (bi_arg->next)
			return (ft_exit_fail_too_many_args());
		else
			ft_exit(ft_atoi(bi_arg->content));
	}
	else
	{
		ft_exit_with_errmsg_numeric(bi_arg->content);
	}
	return (EXIT_SUCCESS);
}
