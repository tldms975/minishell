/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:20 by sielee            #+#    #+#             */
/*   Updated: 2022/08/18 01:31:28 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status;

#include <stdio.h>
void	ft_print(t_pipe_list *pipe)
{
	int				count;
	t_pipe_node		*temp_pipe;
	t_arg_node		*temp_arg;
	t_redir_node	*temp_redir;
	t_limiter_node	*temp_limit;

	count = 0;
	temp_pipe = pipe->head;
	while (temp_pipe != NULL)
	{
		temp_arg = temp_pipe->arg_list->front;
		temp_redir = temp_pipe->redir_list->front;
		temp_limit = temp_pipe->lim_q->front;
		printf ("pipe : %d \n", count++);
		printf("ARG : ");
		while (temp_arg != NULL)
		{
			printf("%s ", temp_arg->content);
			temp_arg = temp_arg->next;
		}
		printf("\n");
		printf("REDIR : ");
		while (temp_redir != NULL)
		{
			printf("%s ", temp_redir->file_name);
			temp_redir = temp_redir->next;
		}
		printf("\n");
		printf("HEREDOC : ");
		while (temp_limit != NULL)
		{
			printf("%s ", temp_limit->data);
			temp_limit = temp_limit->next;
		}
		printf("\n");
		temp_pipe = temp_pipe->next;
	}
}

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
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
	else
		ft_parser(pipe_list, lexer.head, env);
}

int	ft_minishell(t_envp_list *env)
{
	t_pipe_list	pipe_list;
	char	*line;

	g_exit_status = EXIT_SUCCESS;
	while (1)
	{
		ft_default_signal();
		line = readline("minishell$ ");
		if (!line)
			ft_exit(g_exit_status);
		add_history(line);
		ft_parse(&pipe_list, env, line);
		// ft_print(&pipe_list);//for testing
		g_exit_status = ft_execute(&pipe_list, env);
		ft_parser_free(&pipe_list);
		ft_free((void **) &line);
	}
	return (g_exit_status);
}

void	ft_init_terminal(void)
{
	t_term	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_iflag &=  ~ICANON;
	term.c_iflag &=  ~ECHOCTL;
	term.c_iflag &=  ~ISIG;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int ac, char *av[], char *envp[])
{
	t_envp_list	env_list;
	int	ret;

	(void)av;
	if (ac > 1)
		ft_error("Wrong Argc");
	ft_init_terminal();
	ft_init_env_list(&env_list, envp);
	ret = ft_minishell(&env_list);
	return (ret);
}
