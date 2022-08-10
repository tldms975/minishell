/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:35 by sielee            #+#    #+#             */
/*   Updated: 2022/08/10 17:21:03 by sielee           ###   ########seoul.kr  */
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

static void	ft_printf_export(t_envp_list *env_list)
{
	
	
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
