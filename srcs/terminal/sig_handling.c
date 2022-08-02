/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:46:32 by sielee            #+#    #+#             */
/*   Updated: 2022/08/02 18:30:02 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(void)
{
	printf("\033[1A");
	printf("\033[6C");
	printf("exit\n");
	exit(-1);
}

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_signal(void)
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
}
