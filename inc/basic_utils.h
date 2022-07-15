/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:55:38 by sielee            #+#    #+#             */
/*   Updated: 2022/07/15 17:39:14 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_UTILS_H
# define BASIC_UTILS_H

# include "../libft/libft.h"
# include <stddef.h>
# include <stdlib.h>


void	*ft_malloc(size_t size);
int		ft_open(const char *str, int flag);
void	ft_error(char *str);

#endif