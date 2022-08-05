/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:30 by sielee            #+#    #+#             */
/*   Updated: 2022/08/06 04:12:53 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_bi_env(t_cmd *cmd, t_envp_list *env)
{
	char	*line;

	line = *(env->vec);
	while (line)
	{
		printf("%s\n", line);
		line = *(++env->vec);//check
	}
	return (0);
}