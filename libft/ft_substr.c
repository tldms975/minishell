/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:14:09 by sielee            #+#    #+#             */
/*   Updated: 2022/04/01 19:14:25 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s || s_len <= start || len == 0)
		return ((char *)ft_calloc(1, 1));
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (res);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}
