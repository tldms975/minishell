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

<<<<<<< HEAD
typedef int		(*t_function)(t_lexer *lexer);
=======
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

>>>>>>> 27845357d004c2e6717191631accce4df78f60b3

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