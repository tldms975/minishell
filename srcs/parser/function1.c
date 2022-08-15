#include "minishell.h"

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