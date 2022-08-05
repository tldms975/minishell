/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:29:24 by sielee            #+#    #+#             */
/*   Updated: 2022/08/06 01:28:50 by sielee           ###   ########seoul.kr  */
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
