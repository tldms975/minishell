/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:29:24 by sielee            #+#    #+#             */
/*   Updated: 2022/08/07 17:56:33 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_value(t_envp_list *env, const char *key)
{
	t_envp_node	*ptr;

	ptr = env->head;
	while (ptr)
	{
		if (ft_strncmp(ptr->key, key, ft_strlen(key) + 1))
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
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
		env->len = 0;
		env->head = new;
		env->tail = new;
	}
	else
	{
		env->len += 1;
		env->tail->next = new;
		env->tail = new;
	}
}

void	ft_update_env(t_envp_list *env, const char *key, const char *value)
{
	char	*env_value;

	env_value = ft_get_env_value(env, key);
	ft_free((void **) &env_value);
	env_value = ft_strdup(value);
}
