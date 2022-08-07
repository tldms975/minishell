/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:41 by sielee            #+#    #+#             */
/*   Updated: 2022/08/07 22:41:40 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_env_var()
{
	
}

static int	ft_check_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
		{
			ft_putstr_fd("bash: unset: `", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putendl_fd("' not a valid identifier", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_del_env_var(t_envp_list *env, const char *str)
{
	t_envp_node	*prev;
	t_envp_node	*curr;

	
}

int	ft_bi_unset(t_pipe_node *cmd)
{
	t_arg_node	*arg;

	arg = cmd->arg_list->front->next;
	while (arg)
	{

		if (ft_check_valid(arg->content))
			ft_del_env_var(cmd->env_list, arg->content);
		arg = arg->next;
	}
}
