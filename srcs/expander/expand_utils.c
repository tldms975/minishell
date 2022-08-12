/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:11:25 by sielee            #+#    #+#             */
/*   Updated: 2022/07/25 20:16:48 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand_state	check_expand_type(char c)
{
	if (c == '\0')
		return (EX_NULL);
	else if (c == '\'')
		return (EX_SI_QUO);
	else if (c == '\"')
		return (EX_DO_QUO);
	else if (c == '$')
		return (EX_DOLLAR);
	return (EX_NORMAL);
}

t_expand_state check_meta(char c)
{
	if (c == '\"' || c == '\'' || ft_check_meta(c) != NON_META)
		return (EX_META);
	if (c == '$')
		return (EX_DOLLAR);
	return (EX_NORMAL);
}