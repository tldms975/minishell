/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:37:34 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 18:37:37 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	ft_check_meta(char c)
{
	if (c == '\0')
		return (LINE_EOF);
	else if (c == ' ')
		return (MT_SPACE);
	else if (c == '\t')
		return (MT_TAB);
	else if (c == '|')
		return (MT_PIPE);
	else if (c == '&')
		return (MT_AND);
	else if (c == '<')
		return (MT_RIGHT);
	else if (c == '>')
		return (MT_LEFT);
	return (NON_META);
}

t_state	ft_check_type(char c)
{
	t_meta	compare;

	compare = ft_check_meta(c);
	if (compare == LINE_EOF)
		return (ST_NULL);
	else if (compare == MT_SPACE || compare == MT_TAB)
		return (BLANK);
	else if (compare == NON_META)
	{
		if (c == '\'')
			return (SINGLE_QUOTE);
		else if (c == '\"')
			return (DOUBLE_QUOTE);
		return (NORMAL);
	}
	return (META);
}
