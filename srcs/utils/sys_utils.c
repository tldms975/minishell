/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:29:57 by sielee            #+#    #+#             */
/*   Updated: 2022/08/20 18:54:31 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_pipe(int fd[2])
{
	int	ret;

	ret = pipe(fd);
	if (ret == -1)
		ft_perror("pipe");
	return (ret);
}

int	ft_dup2(int fd1, int fd2)
{
	int	ret;

	ret = 0;
	if (fd1 != fd2)
	{
		ret = dup2(fd1, fd2);
		ft_close(fd1);
	}
	if (ret < 0)
	{
		ft_perror("dup2");
	}
	return (ret);
}

pid_t	ft_fork_getting_last_pid(t_pipe_node *pipe_line, t_executor *exec)
{
	int	ret;

	ft_sgh_ign();
	ret = ft_fork();
	if (!pipe_line->next)
		exec->last_pid = ret;
	return (ret);
}

pid_t	ft_fork(void)
{
	pid_t	ret;

	ret = fork();
	if (ret == -1)
		ft_perror("fork");
	return (ret);
}

int	ft_close(int fd)
{
	int	ret;

	ret = 0;
	if (fd > 2)
	{
		ret = close(fd);
	}
	if (ret == -1)
	{
		ft_perror("close");
	}
	return (ret);
}
