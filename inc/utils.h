/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:55:38 by sielee            #+#    #+#             */
/*   Updated: 2022/07/30 02:32:09 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/libft.h"
# include "parser.h"
# include <stddef.h>
# include <stdlib.h>

void	*ft_malloc(size_t size);
void	ft_error(char *str);

int		ft_open(const char *str, int flag);
int		ft_pipe(int	fd[2]);
int		ft_dup2(int fd1, int fd2);


#endif