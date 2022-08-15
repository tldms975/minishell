/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:26:47 by sielee            #+#    #+#             */
/*   Updated: 2022/08/15 17:42:53 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_built_in(t_pipe_node *cmd, int code)
{
	int	(*ft_bi[7])(t_pipe_node *cmd);

	ft_bi[0] = ft_bi_cd;
	ft_bi[1] = ft_bi_echo;
	ft_bi[2] = ft_bi_env;
	ft_bi[3] = ft_bi_exit;
	ft_bi[4] = ft_bi_export;
	ft_bi[5] = ft_bi_pwd;
	ft_bi[6] = ft_bi_unset;
	return (ft_bi[code](cmd));
}

int	ft_check_builtin(t_pipe_node *cmd, t_executor *exec)
{
	const char	*built_in[7] = \
	{"cd", "echo", "env", "exit", "export", "pwd", "unset"};
	char		*target;
	int			i;

	i = 0;
	if (!(cmd->arg_list->front))
		return (FALSE);
	target = cmd->arg_list->front->content;
	while (i < 7)
	{
		if (ft_strncmp(target, built_in[i], \
		(ft_strlen(built_in[i]) + 1)) == 0)
		{
			exec->is_builtin = TRUE;
			exec->built_in_code = i;
			return (exec->is_builtin);
		}
		i++;
	}
	return (FALSE);
}
