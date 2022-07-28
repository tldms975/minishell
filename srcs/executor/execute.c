/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:51 by sielee            #+#    #+#             */
/*   Updated: 2022/07/28 21:31:04 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_exit_status(int status)
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

void	ft_set_fd()
{

}

void	ft_redirection()
{
	// <
	//

	// >
	//

	// >>
	//

	// <<
	// 
}

void	ft_process()
{
	//redirection처리
	// if (dup2(ag->fd_read, STDIN_FILENO) == -1)
	// 	ft_error("dup2 error");
	// if (dup2(ag->fd_write, STDOUT_FILENO) == -1)
	// 	ft_perror("dup2 error");
	// close(ag->fd_write);
	// close(ag->fd_read);
	ft_execute_cmd();
}

int	ft_wait(int pid)
{
	int	stat;
	int	ret;

	ret = -1;
	while ()
	{
		if (waitpid(-1, &stat, 0) == pid)
			ret = ft_get_exit_status(stat);
	}
	return (ret);
}

int	ft_executor()
{
	pid_t	pid;
	int		ret;

	while ()//실행가능단위를 다 실행할때까지
	{
		pid = fork();
		if (pid == -1)
			ft_error("fork error");
		else if (pid == 0)
			ft_process(/*파싱한거,envp*/);
	}
	ret = ft_wait(pid/*, 실행가능한 단위(파이프 수 + 1)*/);
	return (ret);
}

