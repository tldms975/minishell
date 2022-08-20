/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:55:38 by sielee            #+#    #+#             */
/*   Updated: 2022/08/20 19:07:49 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/libft.h"
# include "parser.h"
# include "executor.h"
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>

void	*ft_malloc(size_t size);
void	ft_free(void **ptr);
void	ft_error(char *str);
void	ft_perror(char *str);

void	ft_print_exit(void);
void	ft_exit(int exit_status);

int		ft_pipe(int fd[2]);
int		ft_dup2(int fd1, int fd2);
pid_t	ft_fork_getting_last_pid(t_pipe_node *pipe_line, t_executor *exec);
pid_t	ft_fork(void);
int		ft_close(int fd);

void	ft_init_q(t_limiter_q *queue);
int		ft_is_empty_q(t_limiter_q *queue);
void	ft_enqueue(t_limiter_q **queue, char *data);
void	ft_dequeue(t_limiter_q *queue);

#endif