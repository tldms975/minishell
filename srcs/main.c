/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:20 by sielee            #+#    #+#             */
/*   Updated: 2022/08/01 17:13:55 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_add_history(char *line)
// {
	
// }

void	ft_exit(void)
{
	ft_putstr_fd("\033[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[6C", STDOUT_FILENO);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(-1);
}

int	ft_minishell(char *envp[])
{
	//t_lexer	*cmd_tree;
	char	*line;
	int		exit_code;

	exit_code=-1;
	(void)envp;
	while (1)
	{
		line = readline("bash$ ");
		if (!line)
			ft_exit();
		//ft_add_history(line);
		//cmd_tree = ft_parse(line);
		//exit_code = ft_execute(cmd_tree, envp);
		free(line);
	}
	return (exit_code);
}
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
