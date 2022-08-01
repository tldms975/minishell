/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:29:19 by sielee            #+#    #+#             */
/*   Updated: 2022/08/01 20:14:43 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print(t_lexer lexer)
{
	t_token	*temp;
	int		count;

	count = 0;
	temp = lexer.head;
	while (temp != NULL)
	{
		printf("%s ", temp->content);
		if (temp->type == PIPE)
			count++;
		temp = temp->next;
	}
	printf("pipe : %d\n", count);
}

int	ft_minishell(char *envp[])
{
	//t_cmd_tree	*cmd_tree;
	char	*line;
	int		exit_code;
	t_lexer	lexer;

	exit_code=-1;
	(void)envp;
	while (1)
	{
		line = readline("bash$ ");
		if (!line)
			ft_exit();
		add_history(line);
		lexer_setting(&lexer, line);
		if (ft_lexer(&lexer) < 0)
		{
			ft_putstr_fd("syntax error\n", STDERR_FILENO);
		}
		ft_print(lexer);
		//cmd_tree = ft_parse(line);
		//exit_code = ft_execute(cmd_tree, envp);
		free(line);
	}
	return (exit_code);
}
