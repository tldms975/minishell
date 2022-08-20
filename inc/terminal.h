/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:47:24 by sielee            #+#    #+#             */
/*   Updated: 2022/08/20 19:46:13 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include <termios.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

void	ft_newline_handler(int sig);
void	ft_default_signal(void);
void	ft_sgh_ign(void);

void	ft_init_terminal(void);

void	ft_heredoc_sgh(void);

void	ft_child_sgh(void);

#endif