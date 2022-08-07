/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:33 by sielee            #+#    #+#             */
/*   Updated: 2022/08/07 17:35:58 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnumeric(char *str)
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

int	ft_bi_exit(t_pipe_line *cmd)
{
	t_arg_list *bi_arg;

	bi_arg = cmd->arg->next;
	if (!bi_arg)
	{
		ft_exit(0);
	}
	else if (ft_isnumeric(bi_arg->content))
	{
		if (bi_arg->next)
		{
			ft_print_exit();
			ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
			return (255);
		}
		else
			ft_exit(ft_atoi(bi_arg->content));
	}
	else
	{
		ft_print_exit();
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(bi_arg->content, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
		return (255);
	}
}
