/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:08:46 by sielee            #+#    #+#             */
/*   Updated: 2022/08/01 17:51:44 by sielee           ###   ########seoul.kr  */
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

typedef struct s_executor
{
	pid_t	pid;
	int		fd_read;
	int		fd_write;
	int		pipe_fd[2];
	int		heredoc_fd[2];
}				t_executor;

int	ft_wait_all(int pid, int n);

#endif