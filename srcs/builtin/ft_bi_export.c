/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:35 by sielee            #+#    #+#             */
/*   Updated: 2022/08/05 17:34:15 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_env_value(const char *str, int idx_equal)
{
	char	*key;
	char	*value;

	if (idx_equal == 0)
	{
		key = str;
		value = NULL;
	}
	else
	{
		key = ft_substr(str, 0, idx_equal);
		value = ft_substr(str, idx_equal, ft_strlen(str));
	}

}

static int	ft_check_valid_arg(const char *str, int *idx_equal)
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

int	ft_bi_export(t_cmd *cmd, t_executor *exec)
{
	t_arg_list	*bi_arg;
	int			idx_equal;
	int			exit_status;

	exit_status = 0;
	bi_arg= cmd->arg->next;
	while (bi_arg)
	{
		idx_equal = 0;
		if (ft_check_valid_args(bi_arg, &idx_equal))
			ft_set_env_value(bi_arg, idx_equal);
		else
			exit_status = 1;
		bi_arg = bi_arg->next;
	}
	return (exit_status);
}
