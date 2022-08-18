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

t_expand_state	check_meta(char c)
{
	if (c == '$')
		return (EX_DOLLAR);
	else if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')
		|| ('0' <= c && c <= '9') || c == '_' || c == '?')
		return (EX_NORMAL);
	return (EX_META);
}

t_expand_state	check_meta_qu(char c)
{
	if (c == '$')
		return (EX_DOLLAR);
	else if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')
		|| ('0' <= c && c <= '9') || c == '_')
		return (EX_NORMAL);
	return (EX_META);
}

t_expand_state	check_expand_lim_type(char c)
{
	if (c == '\0')
		return (EX_NULL);
	else if (c == '\'')
		return (EX_SI_QUO);
	else if (c == '\"')
		return (EX_DO_QUO);
	return (EX_NORMAL);
}

t_expand_state	check_expand_heredoc_type(char c)
{
	if (c == '\0')
		return (EX_NULL);
	else if (c == '$')
		return (EX_DOLLAR);
	return (EX_NORMAL);
}
