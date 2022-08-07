/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:59:15 by sielee            #+#    #+#             */
/*   Updated: 2022/08/07 22:59:17 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	ft_sort_env(t_envp_list *env)
// {

// }

int	ft_bi_env(t_pipe_node *cmd)
{
	char	*line;

	//ft_sort_env(cmd->env->vec);
	line = *(cmd->env_list->vec);
	while (line)
	{
		printf("%s\n", line);
		line = *(++cmd->env_list->vec);//check
	}
	return (0);
}
