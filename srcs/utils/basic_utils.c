/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:54:26 by sielee            #+#    #+#             */
/*   Updated: 2022/07/29 22:48:21 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		ft_error("malloc failed");
	return (res);
}
