/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:50:07 by sielee            #+#    #+#             */
/*   Updated: 2022/08/15 02:11:40 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	return (NULL);
}

static size_t	cnt_word(char *s, char c)
{
	size_t	cnt;
	int		i;
	int		tmp;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c))
			i++;
		tmp = i;
		while (s[i] && s[i] != c)
			i++;
		if (s[i] && (tmp != i))
			cnt++;
	}
	return (cnt);
}

static char	**ft_alloc_split(char **res, char *s, char c)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c))
			i++;
		tmp = i;
		while (s[i] && (s[i] != c))
			i++;
		if (s[i] && (tmp != i))
		{
			res[j] = ft_substr(s, tmp, i - tmp);
			if (!res[j++])
				return (free_str(res));
		}
		res[j] = NULL;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)ft_calloc(sizeof(char *), (cnt_word((char *)s, c) + 1));
	if (!res)
		return (NULL);
	if (!ft_alloc_split(res, (char *)s, c))
	{
		free(res);
		res = NULL;
	}
	return (res);
}
