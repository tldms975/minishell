/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_sgh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:52:26 by sielee            #+#    #+#             */
/*   Updated: 2022/08/20 20:03:52 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_escape_child(int sig)
{
	if (sig == SIGINT)
	{
		exit(g_exit_status);
	}
}

void	ft_child_sgh(void)
{
	signal(SIGINT, ft_escape_child);
	signal(SIGQUIT, SIG_IGN);
}
