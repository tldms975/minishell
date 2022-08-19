/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:35 by sielee            #+#    #+#             */
/*   Updated: 2022/08/19 18:59:08 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils.h"
# include "terminal.h"
# include "parser.h"
# include "executor.h"
# include "builtin.h"
# include "envp.h"
# include "expander.h"

int	g_exit_status;

#endif