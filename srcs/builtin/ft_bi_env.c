/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:30 by sielee            #+#    #+#             */
/*   Updated: 2022/08/07 17:35:14 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_bi_env(t_pipe_line *cmd)
{
	char	*line;

	line = *(cmd->env->vec);
	while (line)
	{
		printf("%s\n", line);
		line = *(++cmd->env->vec);//check
	}
	return (0);
}