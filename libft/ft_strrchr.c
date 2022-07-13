/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 02:17:32 by sielee            #+#    #+#             */
/*   Updated: 2022/04/01 19:14:36 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;
	char	ch;

	i = ft_strlen(s);
	ptr = (char *)s;
	ch = (char)c;
	if (!ch)
		return (&ptr[ft_strlen(s)]);
	while (i > -1)
	{
		if (*(ptr + i) == ch)
			return (ptr + i);
		i--;
	}
	return (NULL);
}
