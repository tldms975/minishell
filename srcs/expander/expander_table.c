/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/07/25 20:16:48 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expander_table(t_fuc *funct)
{
	(funct->function)[EX_NORMAL][EX_NORMAL] = ft_ex_next_char;
	(funct->function)[EX_NORMAL][EX_SI_QUO] = ft_ex_norm_to_sq;
	(funct->function)[EX_NORMAL][EX_DO_QUO] = ft_ex_norm_to_dq;
	(funct->function)[EX_NORMAL][EX_DOLLAR] = ft_ex_norm_to_dollar;
	(funct->function)[EX_SI_QUO][EX_NORMAL] = ft_ex_next_char;
	(funct->function)[EX_SI_QUO][EX_SI_QUO] = ft_ex_quo_to_quo;
	(funct->function)[EX_SI_QUO][EX_DO_QUO] = ft_ex_next_char;
	(funct->function)[EX_SI_QUO][EX_DOLLAR] = ft_ex_next_char;
	(funct->function)[EX_DO_QUO][EX_NORMAL] = ft_ex_next_char;
	(funct->function)[EX_DO_QUO][EX_SI_QUO] = ft_ex_next_char;
	(funct->function)[EX_DO_QUO][EX_DO_QUO] = ft_ex_quo_to_quo;
	(funct->function)[EX_DO_QUO][EX_DOLLAR] = ft_ex_qou_to_dollar;
	(funct->function)[EX_DOLLAR][EX_NORMAL] = ft_ex_dollar_to;
	(funct->function)[EX_DOLLAR][EX_SI_QUO] = ft_ex_dollar_to;
	(funct->function)[EX_DOLLAR][EX_DO_QUO] = ft_ex_dollar_to;
	(funct->function)[EX_DOLLAR][EX_DOLLAR] = ft_ex_dollar_to;
}

void	ft_expander_heredoc_table(t_fuc *funct)
{
	(funct->function)[EX_NORMAL][EX_NORMAL] = ft_ex_next_char;
	(funct->function)[EX_NORMAL][EX_SI_QUO] = ft_ex_norm_to_sq;
	(funct->function)[EX_NORMAL][EX_DO_QUO] = ft_ex_norm_to_dq;
	(funct->function)[EX_NORMAL][EX_DOLLAR] = ft_ex_norm_to_dollar_heredoc;
	(funct->function)[EX_SI_QUO][EX_NORMAL] = ft_ex_next_char;
	(funct->function)[EX_SI_QUO][EX_SI_QUO] = ft_ex_quo_to_quo;
	(funct->function)[EX_SI_QUO][EX_DO_QUO] = ft_ex_next_char;
	(funct->function)[EX_SI_QUO][EX_DOLLAR] = ft_ex_next_char;
	(funct->function)[EX_DO_QUO][EX_NORMAL] = ft_ex_next_char;
	(funct->function)[EX_DO_QUO][EX_SI_QUO] = ft_ex_next_char;
	(funct->function)[EX_DO_QUO][EX_DO_QUO] = ft_ex_quo_to_quo;
	(funct->function)[EX_DO_QUO][EX_DOLLAR] = ft_ex_qou_to_dollar;
	(funct->function)[EX_DOLLAR][EX_NORMAL] = ft_ex_dollar_to_heredoc;
	(funct->function)[EX_DOLLAR][EX_SI_QUO] = ft_ex_dollar_to_heredoc;
	(funct->function)[EX_DOLLAR][EX_DO_QUO] = ft_ex_dollar_to_heredoc;
	(funct->function)[EX_DOLLAR][EX_DOLLAR] = ft_ex_dollar_to_heredoc;
}
