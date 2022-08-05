/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:04:46 by sielee            #+#    #+#             */
/*   Updated: 2022/08/05 23:45:04 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "envp.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>

int		ft_check_builtin(t_cmd *cmd, t_executor *exec);

int		ft_bi_pwd(t_cmd *cmd, t_executor *exec);
int		ft_bi_cd(t_cmd *cmd, t_executor *exec);
int		ft_bi_echo(t_cmd *cmd, t_executor *exec);
//int		ft_bi_env(t_envp_list *env);
int		ft_bi_export(t_cmd *cmd, t_executor *exec);
int		ft_bi_unset(t_cmd *cmd, t_executor *exec);
int		ft_bi_exit(t_cmd *cmd, t_executor *exec);




#endif
