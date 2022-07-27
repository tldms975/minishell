/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:51 by sielee            #+#    #+#             */
/*   Updated: 2022/07/27 20:25:57 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_stat(int status)
{
	const int	w_status = status & 0177;

	if (w_status == 0)
		return ((status >> 8) & 0x000000ff);
	if (w_status != 0177 && w_status != 0)
		return (w_status);
	return (0);
}

void	ft_execute_cmd()
{
	//path찾기
	//execve(,, envp);
}

void	ft_process()
{

	ft_execute_cmd();
}

int	ft_executor()
{
	pid_t	pid;
	int		status;

	while ()//실행가능단위를 다 실행할때까지
	{
		pid = fork();
		if (pid == -1)
			ft_error("fork error");
		else
		{
			
		}
	}
	return (ft_exit_stat(status));
}

