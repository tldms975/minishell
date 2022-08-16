 #include "minishell.h"

void	ft_ex_qou_to_dollar_sub(t_buffer *buffer)
{
	while (check_meta((buffer->content)[buffer->index]) == EX_NORMAL)
		buffer->index++;
	ft_dollar(&buffer);
	if (ft_check_type(*(buffer->content)) == DOUBLE_QUOTE)
	{
		buffer->curr_state = EX_NORMAL;
		if (ft_check_type((buffer->content)[buffer->index]) != ST_NULL)
		{
			buffer->content += 1;
			buffer->index = 0;
		}
		else if (ft_check_type((buffer->content)[buffer->index]) == ST_NULL)
			buffer->curr_state = EX_NULL;
	}
	else
		buffer->index = 0;
}

int	ft_ex_qou_to_dollar(t_buffer *buffer)
{
	if (check_meta((buffer->content)[buffer->index + 1]) == EX_DOLLAR)
		buffer->index += 2;
	else if (check_meta((buffer->content)[buffer->index + 1]) == EX_META)
		buffer->index++;
	else if (check_meta((buffer->content)[buffer->index + 1]) == EX_NORMAL)
	{
		new_save(&buffer);
		buffer->content += 1;
		if ('0' <= *(buffer->content) && *(buffer->content) <= '9')
		{
			buffer->content++;
			buffer->index = 0;
		}
        else if (*(buffer->content) == '?')
			ft_question_mark(buffer);
		else
			ft_ex_qou_to_dollar_sub(buffer);
	}
	return (0);
}

int	ft_ex_quo_to_quo(t_buffer *buffer)
{
	buffer->curr_state = EX_NORMAL;
	new_save(&buffer);
	if (ft_check_type((buffer->content)[buffer->index]) != ST_NULL)
	{
		buffer->content += 1;
		buffer->index = 0;
	}
	else if (ft_check_type((buffer->content)[buffer->index]) == ST_NULL)
		buffer->curr_state = EX_NULL;
	return (0);
}

void	ft_ex_dollar_to_sub(t_buffer *buffer)
{
    while (check_meta((buffer->content)[buffer->index]) == EX_NORMAL)
		buffer->index++;
	ft_dollar(&buffer);
	if (ft_check_type(*(buffer->content)) == SINGLE_QUOTE)
	{
		buffer->curr_state = EX_SI_QUO;
		buffer->content++;
		buffer->index = 0;
	}
	else if (ft_check_type(*(buffer->content)) == DOUBLE_QUOTE)
	{
		buffer->curr_state = EX_DO_QUO;
		buffer->content++;
		buffer->index = 0;
	}
	else if (check_meta(*(buffer->content)) == EX_META)
	{
		buffer->curr_state = EX_NORMAL;
		if (*(buffer->content) == '\\')
		{
			buffer->content++;
			buffer->index = 0;
		}
	}
}

int	ft_ex_dollar_to(t_buffer *buffer)
{
	if (check_meta((buffer->content)[buffer->index]) == EX_DOLLAR)
	{
		buffer->index++;
		buffer->curr_state = EX_NORMAL;
	}
	else if (check_meta((buffer->content)[buffer->index]) == EX_META)
		buffer->curr_state = EX_NORMAL;
	else if (check_meta((buffer->content)[buffer->index]) == EX_NORMAL)
	{
		buffer->content += 1;
		buffer->index = 0;
		if ('0' <= *(buffer->content) && *(buffer->content) <= '9')
		{
			buffer->content++;
			buffer->curr_state = EX_NORMAL;
		}
        else if (*(buffer->content) == '?')
        {
			ft_question_mark(buffer);
            buffer->curr_state = EX_NORMAL;
        }
		else
			ft_ex_dollar_to_sub(buffer);
	}
	return (0);
}