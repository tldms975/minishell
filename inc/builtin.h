/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:04:46 by sielee            #+#    #+#             */
/*   Updated: 2022/08/19 19:56:06 by sielee           ###   ########seoul.kr  */
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
int	ft_bi_exit_in_parent(t_pipe_node *cmd);
int	ft_bi_exit_in_child(t_pipe_node *cmd);

#endif
