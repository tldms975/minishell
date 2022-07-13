/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:50:07 by sielee            #+#    #+#             */
/*   Updated: 2022/07/13 15:14:29 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_str(char **str, unsigned int i)
{
	while (i--)
		free(str[i]);
	free(str);
	return (NULL);
}

static char	*alloc_word(char *str, char c)
{
	char			*word;
	unsigned int	i;

	i = 0;
	while (str[i] && !(str[i] == c))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (word);
	i = 0;
	while (str[i] && !(str[i] == c))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	if (!word)
		free(word);
	return (word);
}

unsigned int	cnt_word(char *s, char c)
{
	unsigned int	cnt;

	cnt = 0;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s && !(*s == c))
		{
			cnt++;
			while (*s && !(*s == c))
				s++;
		}
	}
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	char			*str;
	unsigned int	i;

	str = (char *)s;
	res = (char **)malloc(sizeof(char *) * (cnt_word(str, c) + 1));
	if (!res)
		return (res);
	i = 0;
	while (*str)
	{
		while (*str && (*str == c))
			str++;
		if (*str && !(*str == c))
		{
			res[i] = alloc_word(str, c);
			if (!(res[i]))
				return (free_str(res, cnt_word(str, c) + 1));
			i++;
			while (*str && !(*str == c))
				str++;
		}
	}
	res[i] = 0;
	return (res);
}
