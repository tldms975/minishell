/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:54:26 by sielee            #+#    #+#             */
/*   Updated: 2022/10/15 01:09:26 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	ft_perror(char *str)
{
	char	*error_msg;

	if (str)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	error_msg = strerror(errno);
	ft_putendl_fd(error_msg, STDERR_FILENO);
}

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		ft_error("malloc failed");
	return (res);
}
