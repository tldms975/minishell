/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:27:04 by sielee            #+#    #+#             */
/*   Updated: 2022/08/06 01:52:11 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_env_var(t_envp_list *env, const char *key, const char *value)
{
	t_envp_node	*new;

	new = (t_envp_node *)ft_malloc(sizeof(t_envp_node) * 1);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!env->head)
	{
		env->head = new;
		env->tail = new;
	}
	else
	{
		env->tail->next = new;
		env->tail = new;
	}
}

static int	ft_get_idx_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	ft_init_env_list(t_envp_list *env, char *envp[])
{
	char		*line;
	char		*key;
	char		*value;
	int			idx_equal;

	env->head = NULL;
	env->tail = NULL;
	line = *envp;
	while (line)
	{
		idx_equal = ft_get_idx_equal(line);
		key = ft_substr(line, 0, idx_equal);
		value = ft_substr(line, idx_equal + 1, \
		ft_strlen(line) - ft_strlen(key) - 1);
		ft_add_env_var(env, key, value);
		ft_free((void **) &key);
		ft_free((void **) &value);
		envp++;
		line = *envp;
	}
}
