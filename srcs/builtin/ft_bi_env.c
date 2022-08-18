/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:59:15 by sielee            #+#    #+#             */
/*   Updated: 2022/08/18 20:11:18 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_bi_env(t_pipe_node *cmd)
{
	t_envp_node	*env;
	char		*line;

	env = cmd->env_list->head;
	if (!env)
		return (EXIT_SUCCESS);
	line = ft_make_env_line(env);
	while (line)
	{
		printf("%s\n", line);
		free(line);
		env = env->next;
		if (env)
			line = ft_make_env_line(env);
		else
			break ;
	}
	return (EXIT_SUCCESS);
}
