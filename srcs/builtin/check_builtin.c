/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:26:47 by sielee            #+#    #+#             */
/*   Updated: 2022/08/03 19:54:29 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_builtin(t_cmd *cmd, t_executor *exec)
{
	const char	*builtin[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	t_arg_list	*tmp_arg;
	int			i;

	tmp_arg = cmd->arg;
	i = 0;
	while (ft_strncmp(*builtin[i], )
	{
		i++;
	}
}
