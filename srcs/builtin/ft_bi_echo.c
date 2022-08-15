/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:24 by sielee            #+#    #+#             */
/*   Updated: 2022/08/15 15:57:22 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo_args(t_arg_node *arg)
{
	while (arg)
	{
		printf("%s", arg->content);
		arg = arg->next;
		if (arg)
			printf(" ");
	}
}

int	ft_bi_echo(t_pipe_node *cmd)
{
	t_arg_node	*arg;

	arg = cmd->arg_list->front->next;
	if (!arg)
	{
		ft_putendl_fd("", STDOUT_FILENO);
	}
	else
	{
		if (ft_strncmp(arg->content, "-n", 3) == 0)
			ft_echo_args(arg->next);
		else
		{
			ft_echo_args(arg);
			printf("\n");
		}
	}
	return (EXIT_SUCCESS);
}
