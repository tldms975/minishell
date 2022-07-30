/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:20 by sielee            #+#    #+#             */
/*   Updated: 2022/07/31 05:37:50 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	if (sig != 0)
	{
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

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
	signal(SIGINT, handler);
	while (1)
	{
		char *line;
		line = readline("bash$ ");
		if (!line)
			break ;
		free(line);
		ret = 1;/*ft_executor(, envp);*/
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	return (ret);
}
