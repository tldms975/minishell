/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:20 by sielee            #+#    #+#             */
/*   Updated: 2022/07/29 22:43:09 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	int ret;

	ret = -1;
	if (ac > 1)
		ft_error("Wrong Argc\n");
	//init
	//minishell_loop: readline > parse > execute
	// while (1)
	// {

	// 	ret = ft_executor(파싱한거,envp);
	// }
	return (ret);
}
