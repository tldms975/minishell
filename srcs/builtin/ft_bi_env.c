/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:59:15 by sielee            #+#    #+#             */
/*   Updated: 2022/08/08 02:46:04 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	ft_sort_env(t_envp_list *env)
// {

// }

int	ft_bi_env(t_pipe_node *cmd)
{
	t_envp_node	*env;
	char		*line;

	//ft_sort_env(cmd->env->vec);
	env = cmd->env_list->head;
	line = ft_get_env_vector(env);
	while (line)
	{
		printf("%s\n", line);
		env = env->next;
		line = ft_make_env_line(env);
		ft_free((void **)line);
	}
	return (0);
}
