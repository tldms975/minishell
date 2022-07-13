/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:12:25 by sielee            #+#    #+#             */
/*   Updated: 2022/04/01 19:20:28 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	size_t			len;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	len = 0;
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	if (start == end + 1)
		return (ft_calloc(1, 1));
	while (ft_strchr(set, s1[end]))
		end--;
	len = end - start + 1;
	return (ft_substr(s1, start, len));
}
