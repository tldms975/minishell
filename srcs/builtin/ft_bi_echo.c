/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:24 by sielee            #+#    #+#             */
/*   Updated: 2022/08/16 19:59:27 by sielee           ###   ########seoul.kr  */
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

static int	ft_check_echo_options(t_arg_node *arg, int flag)
{
	char	*str;
	int		i;

	while (arg && (arg->content[0] == '-'))
	{
		str = arg->content;
		i = 1;
		while (str[i] && str[i] == 'n')
			i++;
		if (!str[i])
		{
			flag = TRUE;
			arg = arg->next;
		}
		else if (flag == TRUE)
		{
			ft_echo_args(arg);
			return (TRUE);
		}
		else
			return (FALSE);
	}
	if (flag == TRUE)
		ft_echo_args(arg);
	return (flag);
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
		if (!ft_check_echo_options(arg, FALSE))
		{
			ft_echo_args(arg);
			printf("\n");
		}
	}
	return (EXIT_SUCCESS);
}
