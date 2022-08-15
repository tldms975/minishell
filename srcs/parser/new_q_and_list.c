#include "minishell.h"

t_limiter_q	*new_limiter_q(void)
{
	t_limiter_q	*new;

	new = ft_malloc(sizeof(t_limiter_q));
	new->front = NULL;
	new->rear = NULL;
	new->cnt = 0;
	return (new);
}

t_redir_list	*new_redir_list(void)
{
	t_redir_list	*new;

	new = ft_malloc(sizeof(t_redir_list));
	new->front = NULL;
	new->rear = NULL;
	return (new);
}

t_arg_list	*new_arg_list(void)
{
	t_arg_list	*new;

	new = ft_malloc(sizeof(t_arg_list));
	new->front = NULL;
	new->rear = NULL;
	new->cnt = 0;
	return (new);
}