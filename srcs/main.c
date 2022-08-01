/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:20 by sielee            #+#    #+#             */
/*   Updated: 2022/08/01 17:29:35 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	int	ret;

	(void)av;
	ret = -1;
	if (ac > 1)
		ft_error("Wrong Argc\n");
	//init
	ft_signal();
	ret = ft_minishell(envp);
	//ft_free
	return (ret);
}
