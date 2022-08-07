/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:30 by sielee            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/07 21:02:53 by sielee           ###   ########seoul.kr  */
=======
/*   Updated: 2022/08/07 21:42:09 by sielee           ###   ########seoul.kr  */
>>>>>>> ff292cba4812a7e9f1fd65bf75af118e556cb79c
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
