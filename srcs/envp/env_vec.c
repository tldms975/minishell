/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:00:46 by sielee            #+#    #+#             */
/*   Updated: 2022/08/08 22:06:19 by sielee           ###   ########seoul.kr  */
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

char	**ft_get_env_vector(t_envp_list *env)//소팅을 이  메메모모리리에에서서하하면 static으로 선언해도 됨
{
	t_envp_node	*env_node;
	char		**res;
	int			i;

	i = 0;
	env_node = env->head;
	res = (char **)ft_malloc(sizeof(char *) * (env->len + 1));
	while (i < env->len)
	{
		res[i] = ft_make_env_line(env_node);
		env_node = env_node->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
