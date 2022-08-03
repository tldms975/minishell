/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:26:47 by sielee            #+#    #+#             */
/*   Updated: 2022/08/03 21:17:23 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run_builtin(t_cmd *cmd, t_executor *exec, int code)
{
	if (code == B_ECHO)
		ft_echo(cmd, exec);
	else if (code == B_CD)
		ft_cd(cmd, exec);
	else if (code == B_PWD)
		ft_pwd(cmd, exec);
	else if (code == B_EXPORT)
		ft_export(cmd, exec);
	else if (code == B_UNSET)
		ft_unset(cmd, exec);
	else if (code == B_ENV)
		ft_env(cmd, exec);
	else if (code == B_EXIT)
		ft_exit(cmd, exec);
}

int	ft_is_builtin(t_cmd *cmd, t_executor *exec)
{
	const char	*builtin[7] = \
	{"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			i;
//TODO: option도 확인해보기, option에 따라 builtin 아닐수도 있는지 알아보기
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmd->arg->content, *builtin[i], \
		(ft_strlen(builtin[i]) + 1)) == 0)
		{
			exec->builtin_code = i + 1;
			return (1);
		}
		i++;
	}
	return (0);
}
