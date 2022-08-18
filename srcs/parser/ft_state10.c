/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state10.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:37:05 by iyun              #+#    #+#             */
/*   Updated: 2022/08/18 18:37:06 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state_num	ft_state_10(t_action_state **state, t_token_type type)
{
	if (type == DOLLAR)
	{
		reduce_1(state);
		return (STATE_STAY);
	}
	return (STATE_ERR);
}
