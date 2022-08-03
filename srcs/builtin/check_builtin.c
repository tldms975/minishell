/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:26:47 by sielee            #+#    #+#             */
/*   Updated: 2022/08/03 19:48:56 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_builtin(t_cmd *cmd, t_executor *exec)
{
	char		*builtin[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	t_arg_list	*tmp_arg;
	

	tmp_arg = cmd->arg;
	while (tmp_arg)
	{
		while (*builtin[i])
		tmp_arg = tmp_cmd->arg->next;
	}
}
