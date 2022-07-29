/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:11:50 by sielee            #+#    #+#             */
/*   Updated: 2022/07/30 02:06:52 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_limiter_node
{
	struct s_limiter_node	*next;
	char					*data;
}				t_limiter_node;

typedef struct s_limiter_q
{
	struct s_limiter_node	*front;
	struct s_limiter_node	*rear;
	int						cnt;
}				t_limiter_q;


typedef struct s_token
{
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_lexer
{
	t_token		*head;
	t_token		*tail;
	char		*input_line;
}				t_lexer;


#endif