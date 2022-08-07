/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:20 by sielee            #+#    #+#             */
/*   Updated: 2022/08/07 19:06:01 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	t_envp_list	env_list;
	int	ret;

	(void)av;
	(void)envp;
	ret = 0;
	if (ac > 1)
		ft_error("Wrong Argc\n");
	ft_init_env_list(&env_list, envp);
	ret = ft_minishell(&env_list);
	return (ret);
}
