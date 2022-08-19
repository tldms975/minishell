/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sgh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:55:52 by sielee            #+#    #+#             */
/*   Updated: 2022/08/19 21:35:59 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_escape_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = EXIT_FAILURE;
		exit(g_exit_status);
	}
}

void	ft_heredoc_sgh_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_heredoc_sgh(void)
{
	signal(SIGINT, ft_escape_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
