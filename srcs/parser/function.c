#include "minishell.h"

t_token_type		choose_type(t_token *new)
{
	if (!ft_strncmp(new->content, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(new->content, "<", 2))
		return (REDIR_IN);
	else if (!ft_strncmp(new->content, ">", 2))
		return (REDIR_OUT);
	else if (!ft_strncmp(new->content, "<<", 3))
		return (REDIR_HEREDOC);
	else if (!ft_strncmp(new->content, ">>", 3))
		return (REDIR_APPEND);
	else if (ft_check_meta(*(new->content)) == NON_META)
		return (ID);
	return (ERR);

}

t_token	*new_content(t_lexer *lexer)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token));
	new->next = NULL;
	new->content = ft_substr(lexer->last_save_addr, 0, lexer->index);
	if (!new->content)
		exit (-1);
	new->type = choose_type(new->content);
	if ((lexer->last_save_addr)[lexer->index] != ST_NULL)
	{
		lexer->last_save_addr += lexer->index;
		lexer->index = 1;
	}
	if (lexer->head)
		lexer->tail->next = new;
	else
		lexer->head = new;
	return (new);
}

int	ft_next_char(t_lexer *lexer)
{
	lexer->index++;
	return (0);
}

int	ft_norm_to_blank(t_lexer *lexer)
{
	lexer->curr_state = BLANK;
	lexer->tail = new_content(lexer);
	if (lexer->tail->type == ERR)
		return (-1);
	return (0);
}

int	ft_norm_to_sq(t_lexer *lexer)
{
	lexer->curr_state = SINGLE_QUOTE;
	lexer->index++;
	return (0);
}

int	ft_norm_to_dq(t_lexer *lexer)
{
	lexer->curr_state = DOUBLE_QUOTE;
	lexer->index++;
	return (0);
}

int	ft_norm_to_meta(t_lexer *lexer)
{
	lexer->curr_state = META;
	lexer->tail = new_content(lexer);
	if (lexer->tail->type == ERR)
		return (-1);
	return (0);
}

int	ft_blank_to_norm(t_lexer *lexer)
{
	lexer->curr_state = NORMAL;
	lexer->last_save_addr += lexer->index;
	lexer->index = 1;
	return (0);
}

int	ft_blank_to_sq(t_lexer *lexer)
{
	lexer->curr_state = SINGLE_QUOTE;
	lexer->last_save_addr += lexer->index;
	lexer->index = 1;
	return (0);
}

int	ft_blank_to_dq(t_lexer *lexer)
{
	lexer->curr_state = DOUBLE_QUOTE;
	lexer->last_save_addr += lexer->index;
	lexer->index = 1;
	return (0);
}

int	ft_blank_to_meta(t_lexer *lexer)
{
	lexer->curr_state = META;
	lexer->last_save_addr += lexer->index;
	lexer->index = 1;
	return (0);
}

int	ft_quote_to_quote(t_lexer *lexer)
{
	lexer->curr_state = NORMAL;
	lexer->index++;
	return (0);
}

int	ft_meta_to_norm(t_lexer *lexer)
{
	lexer->curr_state = NORMAL;
	lexer->tail = new_content(lexer);
	if (lexer->tail->type == ERR)
		return (-1);
	return (0);
}

int	ft_meta_to_blank(t_lexer *lexer)
{
	lexer->curr_state = BLANK;
	lexer->tail = new_content(lexer);
	if (lexer->tail->type == ERR)
		return (-1);
	return (0);
}

int	ft_meta_to_sq(t_lexer *lexer)
{
	lexer->curr_state = SINGLE_QUOTE;
	lexer->tail = new_content(lexer);
	if (lexer->tail->type == ERR)
		return (-1);
	return (0);
}

int	ft_meta_to_dq(t_lexer *lexer)
{
	lexer->curr_state = DOUBLE_QUOTE;
	lexer->tail = new_content(lexer);
	if (lexer->tail->type == ERR)
		return (-1);
	return (0);
}

int	ft_meta_to_meta(t_lexer *lexer)
{
	char	here;
	char	next;

	here = (lexer->last_save_addr)[lexer->index - 1];
	next = (lexer->last_save_addr)[lexer->index];
	if (here != next)
	{
		lexer->tail = new_content(lexer);
		if (lexer->tail->type == ERR)
			return (-1);
		return (0);
	}
	else
		lexer->index++;
	return (0);
}