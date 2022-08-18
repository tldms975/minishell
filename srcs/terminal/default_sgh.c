/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_sgh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:46:32 by sielee            #+#    #+#             */
/*   Updated: 2022/08/18 17:50:22 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_status;

void	ft_newline_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = EXIT_FAILURE;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_default_signal(void)
{
	signal(SIGINT, ft_newline_handler);
	signal(SIGQUIT, SIG_IGN);
}
