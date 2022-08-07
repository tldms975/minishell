/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:27:04 by sielee            #+#    #+#             */
/*   Updated: 2022/08/07 18:07:41 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_make_env_line(t_envp_node *node)
{
	char	*res;

	res = ft_strdup(node->key);
	res = ft_strjoin(res, "=");
	res = ft_strjoin(res, node->value);
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
	env->vec = ft_get_env_vector(env);
}
