/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:29:19 by sielee            #+#    #+#             */
/*   Updated: 2022/08/05 22:46:26 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print(t_pipe_line *pipe)
{
	int				count;
	t_pipe_line		*temp_pipe;
	t_cmd			*temp_cmd;
	t_arg_list		*temp_arg;
	t_redir_list	*temp_redir;
	t_limiter_node	*temp_limit;

	count = 1;
	temp_pipe = pipe;
	while (temp_pipe != NULL)
	{
		temp_cmd = temp_pipe->cmd;
		temp_arg = temp_cmd->arg;
		temp_redir = temp_cmd->redir;
		temp_limit = temp_cmd->lim_q->front;
		printf ("pipe %d \n", count++);
		while (temp_cmd != NULL)
		{
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
		}
		temp_pipe = temp_pipe->next_pipe;
	}
}

int	ft_minishell(t_envp_list *env)
{
	t_pipe_head	pipe_head;
	char	*line;
	int		exit_code;
	t_lexer	lexer;

	exit_code=0;
	(void)env;
	while (1)
	{
		ft_default_signal();
		line = readline("bash$ ");
		if (!line)
			ft_exit(exit_code);
		add_history(line);
		lexer_setting(&lexer, line);
		if (ft_lexer(&lexer) < 0)
			ft_putstr_fd("syntax error\n", STDERR_FILENO);
		else
			ft_parser(&pipe_head, lexer.head);
		ft_print(pipe_head.head);
		//cmd_tree = ft_parse(line);
		//exit_code = ft_execute(cmd, env);
		free(line);
	}
	return (exit_code);
}
