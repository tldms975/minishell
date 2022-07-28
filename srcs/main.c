/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:20 by sielee            #+#    #+#             */
/*   Updated: 2022/07/28 21:17:46 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char **envp)
{
	int ret;//구조체 큰거 하나에 담는게 좋을듯

	if (ac > 1)
		ft_error("Wrong Argc\n");
	//init: 인자 담기 및 파싱
	//minishell_loop: readline > parse > execute
	// while (1)
	// {

	// 	ret = ft_executor(/*파싱한거,envp*/);
	// }
	return (ret);
}
