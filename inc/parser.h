/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:50 by sielee            #+#    #+#             */
/*   Updated: 2022/07/29 00:27:26 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef int		(*t_function)(t_lexer *lexer);

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_lexer
{
	t_token		*head;
	t_token		*tail;
	t_function	function[5][5];
	char		*input_line;
	int			index;
	int			last_meta;
}				t_lexer;


#endif