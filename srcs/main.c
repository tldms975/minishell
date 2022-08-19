/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:20 by sielee            #+#    #+#             */
/*   Updated: 2022/08/19 21:31:23 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse(t_pipe_list *pipe_list, t_envp_list *env, char *line)
{
	t_lexer		lexer;

	pipe_list->head = NULL;
	pipe_list->tail = NULL;
	pipe_list->cnt_pipe = -1;
	if (ft_strncmp(line, "", 2) == 0)
		return ;
	lexer_setting(&lexer, line);
	if (ft_lexer(&lexer) < 0)
	{
		ft_token_free(&lexer);
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
	}
	else if (ft_parser(pipe_list, lexer.head, env) < 0)
		ft_token_free(&lexer);
}

int	ft_minishell(t_envp_list *env)
{
	t_pipe_list	pipe_list;
	char		*line;

	g_exit_status = EXIT_SUCCESS;
	while (1)
	{
		ft_default_signal();
		line = readline("minishell$ ");
		if (!line)
			ft_exit(g_exit_status);
		add_history(line);
		ft_parse(&pipe_list, env, line);
		g_exit_status = ft_execute(&pipe_list, env);
		ft_parser_free(&pipe_list);
		ft_free((void **) &line);
	}
	return (g_exit_status);
}

int	main(int ac, char *av[], char *envp[])
{
	t_envp_list	env_list;
	int			ret;

	(void)av;
	if (ac > 1)
		ft_error("Wrong Argc");
	ft_init_terminal();
	ft_init_env_list(&env_list, envp);
	ret = ft_minishell(&env_list);
	return (ret);
}
