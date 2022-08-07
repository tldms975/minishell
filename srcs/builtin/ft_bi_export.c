/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:35 by sielee            #+#    #+#             */
/*   Updated: 2022/08/08 01:53:31 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_env_var(const char *str, t_envp_list *env, int idx_equal)
{
	char	*key;
	char	*value;

	if (idx_equal == 0)
	{
		idx_equal = ft_strlen(str);
	}
	key = ft_substr(str, 0, idx_equal);
	value = ft_substr(str, idx_equal + 1, ft_strlen(str) - ft_strlen(key) - 1);
	ft_add_env_var(env, key, value);
	ft_free(key);
	ft_free(value);
}

static int	ft_check_valid(const char *str, int *idx_equal)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 0 && str[i] == '=')
		{
			*idx_equal = i;
			return (1);
		}
		else if (!ft_isalpha(str[i]))
		{
			ft_putstr_fd("bash: export: `", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putendl_fd("' not a valid identifier", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_bi_export(t_pipe_node *cmd)
{
	t_arg_node	*bi_arg;
	int			idx_equal;
	int			exit_status;

	exit_status = EXIT_SUCCESS;
	bi_arg = cmd->arg_list->front->next;
	while (bi_arg)
	{
		idx_equal = 0;
		if (ft_check_valid(bi_arg, &idx_equal))
			ft_set_env_var(bi_arg, cmd->env_list, idx_equal);
		else
			exit_status = EXIT_FAILURE;
		bi_arg = bi_arg->next;
	}
	return (exit_status);
}
