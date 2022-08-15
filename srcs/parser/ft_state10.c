#include "minishell.h"

t_state_num ft_state_10(t_action_state **state, t_token_type type)
{
	if (type == DOLLAR)
	{
		reduce_1(state);
		return (STATE_STAY);
	}
	return (STATE_ERR);
}