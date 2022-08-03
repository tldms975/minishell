/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:04:46 by sielee            #+#    #+#             */
/*   Updated: 2022/08/03 21:16:36 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>


int		ft_is_builtin(t_cmd *cmd, t_executor *exec);
void	ft_run_builtin(t_cmd *cmd, t_executor *exec, int code);


#endif
