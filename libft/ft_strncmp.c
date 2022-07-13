/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:41:55 by sielee            #+#    #+#             */
/*   Updated: 2022/04/01 19:14:49 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*unch_s1;
	unsigned char	*unch_s2;

	unch_s1 = (unsigned char *)s1;
	unch_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((unch_s1[i] || unch_s2[i]) && i < n)
	{
		if (unch_s1[i] != unch_s2[i])
			return (unch_s1[i] - unch_s2[i]);
		i++;
	}
	return (0);
}
