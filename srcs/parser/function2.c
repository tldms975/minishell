#include "minishell.h"

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
