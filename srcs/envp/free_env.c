/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:51:38 by sielee            #+#    #+#             */
/*   Updated: 2022/08/13 20:24:49 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env_list(t_envp_list *env_list)
{
	t_envp_node	*env;
	t_envp_node	*tmp;

	env = env_list->head;
	while (env)
	{
		ft_free((void **) &env->key);
		ft_free((void **) &env->value);
		tmp = env->next;
		ft_free((void **) &env);
		env = tmp;
	}
	ft_free((void **) &env_list->head);
	ft_free((void **) &env_list->tail);
	ft_free((void **) &env_list->vec);
	ft_free((void **) &env_list->len);
}