#include "minishell.h"

void    lexer_setting(t_lexer *lexer, char *input_line)
{
    lexer->index = 1;
    lexer->input_line = input_line;
    lexer->last_save_addr = input_line;
    lexer->curr_state = ft_check_type(*input_line);
    lexer->head = NULL;
    lexer->tail = NULL;
}

int ft_lexer(t_lexer *lexer)
{
    
}