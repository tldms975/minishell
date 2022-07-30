#include "minishell.h"

t_meta	ft_check_meta(char c)
{
	if (c == '\0')
		return (EOF);
	else if (c == ' ')
		return (SPACE);
	else if (c == '\t')
		return (TAB);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (RIGHT);
	else if (c == '>')
		return (LEFT);
	return (NON_META);
}

t_state	ft_check_type(char c)
{
	t_meta	compare;

	compare = ft_check_meta(c);
	if (compare == EOF)
		return (ST_NULL);
	else if (compare == SPACE || compare == TAB)
		return (BLANK);
	else if (compare == NON_META)
	{
		if (c == '\'')
			return (SINGLE_QUOTE);
		else if (c == '\"')
			return (DOUBLE_QUOTE);
		return (NORMAL);
	}
	return (META);
}