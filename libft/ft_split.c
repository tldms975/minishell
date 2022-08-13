/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:50:07 by sielee            #+#    #+#             */
/*   Updated: 2022/08/13 18:19:05 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_str(char **str, unsigned int i)
{
	while (i--)
		free(str[i]);
	free(str);
	str = NULL;
	return (NULL);
}

static char	*alloc_word(char *str, char c)
{
	char			*word;
	unsigned int	len;

	len = 0;
	while (str[len] && !(str[len] == c))
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	len = 0;
	while (str[len] && !(str[len] == c))
	{
		word[len] = str[len];
		len++;
	}
	word[len] = '\0';
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

static void	*ft_valid_malloc(char *s, size_t size)
{
	void	*res;

	if (!s)
		return (s);
	res = malloc(size);
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	char			*str;
	unsigned int	i;

	str = (char *)s;
	res = (char **)ft_valid_malloc(str, sizeof(char *) * cnt_word(str, c) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str && (*str == c))
			str++;
		if (*str && !(*str == c))
		{
			res[i] = alloc_word(str, c);
			if (!(res[i]))
				return (free_str(res, i));
			i++;
			while (*str && !(*str == c))
				str++;
		}
	}
	res[i] = NULL;
	return (res);
}
