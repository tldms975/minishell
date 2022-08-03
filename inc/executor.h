/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:08:46 by sielee            #+#    #+#             */
/*   Updated: 2022/08/04 02:22:45 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>
# include "parser.h"

enum e_read_write
{
	READ,
	WRITE
};

typedef struct s_executor	t_executor;

struct s_executor
{
	pid_t	pid;
	int		fd_read;
	int		fd_write;
	int		pipe_fd[2];
	int		heredoc_fd[2];
	int		is_built_in;
	int		built_in_code;
	int		cnt_child;
};

int		ft_get_exit_status(int status);

void	ft_check_heredoc(t_limiter_q *lim_q, t_executor *exec);
void	ft_heredoc(t_limiter_q *lim_q, t_executor *exec);
void	ft_read_heredoc(t_executor *exec, char *limiter);

void	ft_redirection(enum e_token_type type, const char *file_name, \
t_executor *exec);

int	ft_wait_all_child(int pid, int n);

#endif