/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:54:26 by sielee            #+#    #+#             */
/*   Updated: 2022/08/02 18:39:19 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_error(const char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	ft_perror(const char *str)
{
	char	*error_msg;
	char	*ret_msg;

	error_msg = strerror(errno);
	ret_msg = ft_strjoin(error_msg, str);
	ft_putendl_fd(ret_msg, STDERR_FILENO);
}

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		ft_error("malloc failed");
	return (res);
}
