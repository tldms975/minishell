/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:55:38 by sielee            #+#    #+#             */
/*   Updated: 2022/07/31 02:44:07 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/libft.h"
# include "parser.h"
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>

void	*ft_malloc(size_t size);
void	ft_error(char *str);

int		ft_open(const char *str, int flag);
int		ft_pipe(int fd[2]);
int		ft_dup2(int fd1, int fd2);
pid_t	ft_fork(void);

void	ft_init_q(t_limiter_q *queue);
int		ft_is_empty_q(t_limiter_q *queue);
void	ft_enqueue(t_limiter_q *queue, char *data);
void	ft_dequeue(t_limiter_q *queue);

#endif