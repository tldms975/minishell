#include "minishell.h"

void	ft_arg_id(t_pipe_node **pipe, t_token **token)
{
	t_token	*temp;

	ft_enqueue_arg(pipe, (*token)->content);
	temp = *token;
	(*token) = (*token)->next;
	free(temp);
}

int	ft_arg_redir_in(t_pipe_node **pipe, t_token **token)
{
	t_token	*temp;

	free((*token)->content);
	temp = (*token);
	(*token) = (*token)->next;
	free(temp);
	if ((*token)->type == ID)
	{
		ft_enqueue_redir(pipe, REDIR_IN, (*token)->content);
		temp = *token;
		(*token) = (*token)->next;
		free(temp);
	}
	else
		return (-1);
	return (0);
}

int	ft_arg_redir_out(t_pipe_node **pipe, t_token **token)
{
	t_token	*temp;

	free((*token)->content);
	temp = (*token);
	(*token) = (*token)->next;
	free(temp);
	if ((*token)->type == ID)
	{
		ft_enqueue_redir(pipe, REDIR_OUT, (*token)->content);
		temp = *token;
		(*token) = (*token)->next;
		free(temp);
	}
	else
		return (-1);
	return (0);
}

int	ft_arg_redir_append(t_pipe_node **pipe, t_token **token)
{
	t_token	*temp;

	free((*token)->content);
	temp = (*token);
	(*token) = (*token)->next;
	free(temp);
	if ((*token)->type == ID)
	{
		ft_enqueue_redir(pipe, REDIR_APPEND, (*token)->content);
		temp = *token;
		(*token) = (*token)->next;
		free(temp);
	}
	else
		return (-1);
	return (0);
}

int	ft_arg_heredoc(t_pipe_node **pipe, t_token **token)
{
	t_token	*temp;

	free((*token)->content);
	temp = (*token);
	(*token) = (*token)->next;
	free(temp);
	if ((*token)->type == ID)
	{
		ft_enqueue(&((*pipe)->lim_q), (*token)->content);
		temp = *token;
		(*token) = (*token)->next;
		free(temp);
	}
	else
		return (-1);
	return (0);
}