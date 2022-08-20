/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:35 by sielee            #+#    #+#             */
/*   Updated: 2022/08/21 01:11:29 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_env_var(char *str, t_envp_list *env, int idx_equal)
{
	char	*key;
	char	*value;

	if (idx_equal == 0)
	{
		idx_equal = ft_strlen(str);
	}
	key = ft_substr(str, 0, idx_equal);
	value = ft_substr(str, idx_equal + 1, ft_strlen(str) - ft_strlen(key) - 1);
	if (!value)
		value = ft_strdup("");
	if (ft_get_env_node_ptr(env, key))
		ft_mod_env_value(env, key, value);
	else
		ft_add_env_var(env, key, value);
	ft_free((void **) &key);
	ft_free((void **) &value);
}

static int	ft_check_valid(char *str, int *idx_equal)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 0 && str[i] == '=')
		{
			*idx_equal = i;
			return (TRUE);
		}
		else if (!ft_isalnum(str[i]) || str[i] != '_')
		{
			ft_putstr_fd("bash: export: `", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putendl_fd("' not a valid identifier", STDERR_FILENO);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static void	ft_print_export(t_envp_list *env_list)
{
	t_envp_list	*sorted_list;
	t_envp_node	*sorted;

	if (!env_list->head)
		return ;
	sorted_list = ft_get_sorted_env(env_list);
	if (!sorted_list->head)
		return ;
	sorted = sorted_list->head;
	while (sorted)
	{
		if (sorted->value)
			printf("declare -x %s=\"%s\"\n", sorted->key, sorted->value);
		else
			printf("declare -x %s\n", sorted->key);
		sorted = sorted->next;
	}
	ft_free_env_list(sorted_list);
}

int	ft_bi_export(t_pipe_node *cmd)
{
	t_arg_node	*bi_arg;
	int			idx_equal;
	int			exit_status;

	exit_status = EXIT_SUCCESS;
	bi_arg = cmd->arg_list->front->next;
	if (!bi_arg)
		ft_print_export(cmd->env_list);
	while (bi_arg)
	{
		idx_equal = 0;
		if (ft_check_valid(bi_arg->content, &idx_equal))
			ft_update_env_var(bi_arg->content, cmd->env_list, idx_equal);
		else
			exit_status = EXIT_FAILURE;
		bi_arg = bi_arg->next;
	}
	return (exit_status);
}
