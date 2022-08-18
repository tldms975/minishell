/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:41 by sielee            #+#    #+#             */
/*   Updated: 2022/08/18 20:46:29 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_valid(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
		{
			ft_putstr_fd("bash: unset: `", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
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
		if (ft_check_valid(arg->content))
			ft_del_env_var(cmd->env_list, arg->content);
		else
			exit_code = EXIT_FAILURE;
		arg = arg->next;
	}
	return (exit_code);
}
