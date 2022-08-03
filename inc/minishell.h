/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:35 by sielee            #+#    #+#             */
/*   Updated: 2022/08/04 00:25:46 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils.h"
# include "parser.h"
# include "executor.h"
# include "builtin.h"
# include "terminal.h"

typedef struct s_envp_list	t_envp_list;

struct s_envp_list
{
	char	*key;
	char	*value;
	int		list_len;
	struct s_envp_list	*next;
};

#endif