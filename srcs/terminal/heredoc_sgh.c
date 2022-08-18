/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sgh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:55:52 by sielee            #+#    #+#             */
/*   Updated: 2022/08/19 03:50:00 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_escape_heredoc(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		printf("sigint in heredoc\n");
// 	}
// }

void	ft_heredoc_sgh(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}