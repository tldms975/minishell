/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:22:57 by sielee            #+#    #+#             */
/*   Updated: 2022/04/01 19:15:54 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dest;
	unsigned char	uc_c;
	size_t			i;

	dest = (unsigned char *)b;
	uc_c = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		*dest++ = uc_c;
		i++;
	}
	return (b);
}
