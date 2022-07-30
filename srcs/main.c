/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:20 by sielee            #+#    #+#             */
/*   Updated: 2022/07/31 01:34:10 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	int ret;

	ret = -1;
	(void)av;
	if (ac > 1)
		ft_error("Wrong Argc\n");
	//init
	// minishell_loop: readline > parse > execute
	(void)envp;
	while (1)
	{
		char *str;
		str = readline("bash-3.2$");
		printf("%s\n", str);
		free(str);
		ret = 1;/*ft_executor(, envp);*/
	}
	return (ret);
}
