/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:29:57 by sielee            #+#    #+#             */
/*   Updated: 2022/07/29 23:57:58 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_open(const char *str, int flag)
{
	int	fd;

	fd = open(str, flag);
	if (fd < 0)
		ft_error("open error");
	return (fd);
}

int	ft_pipe(int	fd[2])
{
	int	ret;

	ret = pipe(fd);
	if (ret == -1)
		ft_error("pipe error");
	return (ret);
}

int	ft_dup2(int fd1, int fd2)
{
	int	ret;

	ret = dup2(fd1, fd2);
	if (ret < 0)
		ft_error("dup2 error");
	return (ret);
}