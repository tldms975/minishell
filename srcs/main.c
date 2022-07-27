/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:20 by sielee            #+#    #+#             */
/*   Updated: 2022/07/27 20:22:06 by sielee           ###   ########seoul.kr  */
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
	ret = ;
	return (ret);
}
