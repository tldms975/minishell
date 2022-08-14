/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 16:12:18 by sielee            #+#    #+#             */
/*   Updated: 2022/08/14 21:56:01 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_exit(void)
{
	printf("\033[1A");
	printf("\033[11C");
	printf("exit\n");
}

void	ft_exit(int exit_status)
{
	ft_print_exit();
	exit(exit_status);
}
