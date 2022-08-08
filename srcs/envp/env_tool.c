/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:29:24 by sielee            #+#    #+#             */
/*   Updated: 2022/08/08 16:37:35 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_ptr_env_value(t_envp_list *env, const char *key, \
t_envp_node *position)
{
	t_envp_node	*ptr;

	ptr = env->head;
	while (ptr)
	{
		if (ft_strncmp(ptr->key, key, ft_strlen(key) + 1))
		{
			*position = *ptr;
			return (ptr->value);
		}
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

void	ft_mod_env_value(t_envp_list *env, const char *key, \
const char *new_value)
{
	t_envp_node	position;
	char	*value;

	value = ft_get_ptr_env_value(env, key, &position);
	ft_free((void **) &value);
	value = ft_strdup(new_value);
}
