/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:41 by sielee            #+#    #+#             */
/*   Updated: 2022/08/18 21:02:28 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_valid(t_arg_node *arg)
{
	int	i;

	i = 0;
	while (arg->content[i])
	{
		if (!ft_isalpha(arg->content[i]))
		{
			printf("%s\n", arg->content);
			ft_putstr_fd("bash: unset: `", STDERR_FILENO);
			ft_putstr_fd(arg->content, STDERR_FILENO);
			ft_putendl_fd("' not a valid identifier", STDERR_FILENO);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	ft_bi_unset(t_pipe_node *cmd)
{
	t_arg_node	*arg;
	int			exit_code;

	arg = cmd->arg_list->front->next;
	exit_code = EXIT_SUCCESS;
	while (arg)
	{
		if (ft_check_valid(arg))
			ft_del_env_var(cmd->env_list, arg->content);
		else
			exit_code = EXIT_FAILURE;
		arg = arg->next;
	}
	return (exit_code);
}
