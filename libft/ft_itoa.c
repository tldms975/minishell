/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:46:42 by sielee            #+#    #+#             */
/*   Updated: 2022/04/10 17:36:33 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cnt_digit(int n)
{
	int	cnt;

	cnt = 0;
	if (n < 0)
	{
		n *= -1;
		cnt++;
	}
	else if (n == 0)
		cnt++;
	while (n != 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	char		*res;
	long long	num;
	int			cnt;

	cnt = cnt_digit(n);
	res = (char *)malloc(sizeof(char) * (cnt + 1));
	num = n;
	if (!res)
		return (res);
	if (num < 0)
	{
		res[0] = '-';
		num *= -1;
	}
	else if (num == 0)
		res[0] = '0';
	res[cnt] = '\0';
	while (num != 0)
	{
		cnt--;
		res[cnt] = (num % 10) + '0';
		num /= 10;
	}
	return (res);
}
