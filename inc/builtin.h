/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:04:46 by sielee            #+#    #+#             */
/*   Updated: 2022/08/13 17:01:04 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>

int	ft_bi_pwd(t_pipe_node *cmd);
int	ft_bi_cd(t_pipe_node *cmd);
int	ft_bi_echo(t_pipe_node *cmd);
int	ft_bi_env(t_pipe_node *cmd);
int	ft_bi_export(t_pipe_node *cmd);
int	ft_bi_unset(t_pipe_node *cmd);
int	ft_bi_exit(t_pipe_node *cmd);




#endif
