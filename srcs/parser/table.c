/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/08/01 18:07:28 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_table(t_lexer *lexer)
{
	(lexer->function)[NORMAL][NORMAL] = ft_next_char;
	(lexer->function)[NORMAL][BLANK] = ft_norm_to_blank;
	(lexer->function)[NORMAL][SINGLE_QUOTE] = ft_norm_to_sq;
	(lexer->function)[NORMAL][DOUBLE_QUOTE] = ft_norm_to_dq;
	(lexer->function)[NORMAL][META] = ft_norm_to_meta;
	(lexer->function)[BLANK][NORMAL] = ft_blank_to_norm;
	(lexer->function)[BLANK][BLANK] = ft_next_char;
	(lexer->function)[BLANK][SINGLE_QUOTE] = ft_blank_to_sq;
	(lexer->function)[BLANK][DOUBLE_QUOTE] = ft_blank_to_dq;
	(lexer->function)[BLANK][META] = ft_blank_to_meta;
	(lexer->function)[SINGLE_QUOTE][NORMAL] = ft_next_char;
	(lexer->function)[SINGLE_QUOTE][BLANK] = ft_next_char;
	(lexer->function)[SINGLE_QUOTE][SINGLE_QUOTE] = ft_quote_to_quote;
	(lexer->function)[SINGLE_QUOTE][DOUBLE_QUOTE] = ft_next_char;
	(lexer->function)[SINGLE_QUOTE][META] = ft_next_char;
	(lexer->function)[DOUBLE_QUOTE][NORMAL] = ft_next_char;
	(lexer->function)[DOUBLE_QUOTE][BLANK] = ft_next_char;
	(lexer->function)[DOUBLE_QUOTE][SINGLE_QUOTE] = ft_next_char;
	(lexer->function)[DOUBLE_QUOTE][DOUBLE_QUOTE] = ft_quote_to_quote;
	(lexer->function)[DOUBLE_QUOTE][META] = ft_next_char;
	(lexer->function)[META][NORMAL] = ft_meta_to_norm;
	(lexer->function)[META][BLANK] = ft_meta_to_blank;
	(lexer->function)[META][SINGLE_QUOTE] = ft_meta_to_sq;
	(lexer->function)[META][DOUBLE_QUOTE] = ft_meta_to_dq;
	(lexer->function)[META][META] = ft_meta_to_meta;
}
