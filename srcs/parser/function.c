#include "minishell.h"

int		choose_type(t_token *new)
{
	
}

t_token	*new_content(t_lexer *lexer)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		exit (-1);
	new->next = NULL;
	new->content = ft_substr(lexer->last_save_addr, 0, lexer->index);
	if (!new->content)
		exit (-1);
	lexer->last_save_addr += lexer->index;
	if (lexer->head)
		lexer->tail->next = new;
	else
		lexer->head = new;
	return (0);
}

int	ft_next_char(t_lexer *lexer)
{
	lexer->index++; // state maintain
	return (0);
}

int	ft_norm_to_blank(t_lexer *lexer)
{
	ft_
}