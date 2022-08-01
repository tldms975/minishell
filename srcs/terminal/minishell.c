/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:29:19 by sielee            #+#    #+#             */
/*   Updated: 2022/08/01 17:29:48 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minishell(char *envp[])
{
	//t_cmd_tree	*cmd_tree;
	char	*line;
	int		exit_code;

	exit_code=-1;
	(void)envp;
	while (1)
	{
		line = readline("bash$ ");
		if (!line)
			ft_exit();
		add_history(line);
		//cmd_tree = ft_parse(line);
		//exit_code = ft_execute(cmd_tree, envp);
		free(line);
	}
	return (exit_code);
}
