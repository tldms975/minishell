#include "minishell.h"

void	ft_enqueue_arg(t_pipe_node **pipe, char *data)
{
	t_arg_node	*new;

	new = ft_malloc(sizeof(t_arg_node));
	new->content = data;
	new->next = NULL;
	if ((*pipe)->arg_list->front == NULL)
	{
		(*pipe)->arg_list->front = new;
	}
	else
	{
		(*pipe)->arg_list->rear->next = new;
	}
	(*pipe)->arg_list->rear = new;
	(*pipe)->arg_list->cnt += 1;
}

void	ft_enqueue_redir(t_pipe_node **pipe, t_token_type type, char *data)
{
	t_redir_node	*new;

	new = ft_malloc(sizeof(t_redir_node));
	new->file_name = data;
	new->type = type;
	new->next = NULL;
	if ((*pipe)->redir_list->front == NULL)
	{
		(*pipe)->redir_list->front = new;
	}
	else
	{
		(*pipe)->redir_list->rear->next = new;
	}
	(*pipe)->redir_list->rear = new;
}

int	ft_is_empty_q_pipe(t_pipe_list *queue)
{
	return (queue->cnt_pipe == 0);
}

void	ft_enqueue_pipe(t_pipe_list **queue)
{
	t_pipe_node	*new;

	new = ft_malloc(sizeof(t_pipe_node));
	new->arg_list = new_arg_list();
	new->redir_list = new_redir_list();
	new->lim_q = new_limiter_q();
	new->next = NULL;
	if ((*queue)->head == NULL)
	{
		(*queue)->head = new;
	}
	else
	{
		(*queue)->tail->next = new;
	}
	(*queue)->tail = new;
	(*queue)->cnt_pipe += 1;
}