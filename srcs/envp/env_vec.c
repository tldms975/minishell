/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:00:46 by sielee            #+#    #+#             */
/*   Updated: 2022/08/14 22:21:55 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_make_env_line(t_envp_node *node)
{
	char	*step_one;
	char	*res;

	step_one = ft_strjoin(node->key, "=");
	res = ft_strjoin(step_one, node->value);
	ft_free((void **) &step_one);
	return (res);
}

char	**ft_get_env_vector(t_envp_list *env_list)
{
	t_envp_node	*env;
	char		**res;
	int			i;

	i = 0;
	env = env_list->head;
	res = (char **)ft_malloc(sizeof(char *) * (env_list->len + 1));
	while (env)
	{
		res[i] = ft_make_env_line(env);
		env = env->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
