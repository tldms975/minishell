/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:29:24 by sielee            #+#    #+#             */
/*   Updated: 2022/08/17 02:33:52 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp_node	*ft_get_env_node_ptr(t_envp_list *env, const char *key)
{
	t_envp_node	*target;

	target = env->head;
	while (target)
	{
		if (ft_strncmp(target->key, key, ft_strlen(key) + 1) == 0)
		{
			return (target);
		}
		target = target->next;
	}
	return (NULL);
}

char	*ft_get_env_value_ptr(t_envp_list *env, const char *key)
{
	t_envp_node	*target;

	target = ft_get_env_node_ptr(env, key);
	if (target)
		return (target->value);
	return (NULL);
}

void	ft_del_env_var(t_envp_list *env, char *key)
{
	t_envp_node	*target_node;

	target_node = ft_get_env_node_ptr(env, key);
	if (!target_node)
		return ;
	target_node->prev->next = target_node->next;
	env->len -= 1;
	ft_free((void **) &(target_node->key));
	ft_free((void **) &(target_node->value));
	ft_free((void **) &target_node);
}

void	ft_add_env_var(t_envp_list *env, const char *key, const char *value)
{
	t_envp_node	*new;

	new = (t_envp_node *)ft_malloc(sizeof(t_envp_node) * 1);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!env->head)
	{
		env->len = 1;
		env->head = new;
		env->tail = new;
		new->prev = NULL;
	}
	else
	{
		env->len += 1;
		env->tail->next = new;
		new->prev = env->tail;
		env->tail = new;
	}
}

void	ft_mod_env_value(t_envp_list *env, const char *key, \
const char *new_value)
{
	t_envp_node	*target_node;

	target_node = ft_get_env_node_ptr(env, key);
	ft_free((void **) &(target_node->value));
	target_node->value = ft_strdup(new_value);
}
