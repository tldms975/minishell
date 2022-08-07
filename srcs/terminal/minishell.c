/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:29:19 by sielee            #+#    #+#             */
/*   Updated: 2022/08/07 18:26:05 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print(t_pipe_q *pipe)
{
	int				count;
	t_pipe_node		*temp_pipe;
	t_arg_node		*temp_arg;
	t_redir_node	*temp_redir;
	t_limiter_node	*temp_limit;

	count = 0;
	temp_pipe = pipe->front;
	while (temp_pipe != NULL)
	{
		temp_arg = temp_pipe->arg_q->front;
		temp_redir = temp_pipe->redir_q->front;
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
		temp_pipe = temp_pipe->next_pipe;
	}
}

t_pipe_line	*ft_parse(char *line)
{
	t_lexer		lexer;
	t_pipe_head	pipe_head;

	pipe_head.cnt_pipe = -1;
	lexer_setting(&lexer, line);
	if (ft_lexer(&lexer) < 0)
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
	else
		ft_parser(pipe, lexer.head);
}

int	ft_minishell(t_envp_list *env)
{
	char	*line;
	int		exit_code;

	exit_code = 0;//for the test
	//exit_code = EXIT_FAILURE;
	//(void)env;//for the test
	while (1)
	{
		ft_default_signal();
		line = readline("bash$ ");
		if (!line)
			ft_exit(EXIT_SUCCESS);
		add_history(line);
		exit_code = ft_execute(ft_parse(line), env);
		free(line);
	}
	return (exit_code);
}
