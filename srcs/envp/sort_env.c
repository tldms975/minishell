/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:02:18 by sielee            #+#    #+#             */
/*   Updated: 2022/08/17 14:42:39 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_swap_env_node(t_envp_node *node1, t_envp_node *node2)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = node1->key;
	tmp_value = node1->value;
	node1->key = node2->key;
	node1->value = node2->value;
	node2->key = tmp_key;
	node2->value = tmp_value;
}

static t_envp_list	*ft_dup_env(t_envp_list *env_list)
{
	t_envp_list	*res;
	t_envp_node	*env;

	res = (t_envp_list *)ft_malloc(sizeof(t_envp_list));
	res->head = NULL;
	res->vec = NULL;
	res->tail = NULL;
	env = env_list->head;
	while (env)
	{
		ft_add_env_var(res, env->key, env->value);
		env = env->next;
	}
	return (res);
}

t_envp_list	*ft_get_sorted_env(t_envp_list *env_list)
{
	t_envp_list	*res;
	t_envp_node	*node1;
	t_envp_node	*node2;

	res = ft_dup_env(env_list);
	if (!env_list && !env_list->head)
		return (NULL);
	node1 = res->head;
	while (node1->next)
	{
		node2 = node1->next;
		while (node2)
		{
			if (ft_strncmp(node1->key, node2->key, \
			ft_strlen(node1->key) + 1) > 0)
				ft_swap_env_node(node1, node2);
			node2 = node2->next;
		}
		node1 = node1->next;
	}
	return (res);
}
