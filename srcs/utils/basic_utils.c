/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:54:26 by sielee            #+#    #+#             */
/*   Updated: 2022/07/13 18:55:38 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "basic_utils.h"

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit (1);
}

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		ft_error("malloc failed");
	return (res);
}

int	ft_open(const char *str, int flag)
{
	int	fd;

	fd = open(str, flag);
	if (fd < 0)
		ft_error("open error");
	return (fd);
}
