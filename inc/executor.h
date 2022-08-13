/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:08:46 by sielee            #+#    #+#             */
/*   Updated: 2022/08/13 17:39:15 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>
# include <sys/stat.h>
# include "parser.h"
# include "envp.h"
# include "builtin.h"

typedef struct stat			t_stat;
typedef struct s_executor	t_executor;

enum e_exit_stat
{
	EXIT_UNEXECUTABLE = 126,
	EXIT_NOTFOUND = 127,
	EXIT_OVER = 255
};

enum e_read_write
{
	READ,
	WRITE
};

enum e_true_false
{
	FALSE,
	TRUE
};

struct s_executor
{
	pid_t		pid;
	int			fd_read;
	int			fd_write;
	int			pipe_fd[2];
	int			heredoc_fd[2];
	int			is_built_in;
	int			built_in_code;
	int			cnt_child;
	t_envp_list	*env;
};

int		ft_get_exit_status(int status);

int		ft_check_builtin(t_pipe_node *cmd, t_executor *exec);
int		ft_execute_built_in(t_pipe_node *cmd, int code);

int		ft_execute(t_pipe_list *pipe_list, t_envp_list *env_list);
void	ft_execute_cmd(t_arg_list *arg_list, t_envp_list *env);

int		ft_exe_parent_process(t_pipe_node *cmd, t_executor *exec);
void	ft_exe_child_process(t_pipe_node *cmd, t_executor *exec);

void	ft_check_heredoc(t_limiter_q *lim_q, t_executor *exec);
void	ft_heredoc(t_limiter_q *lim_q, t_executor *exec);

void	ft_redirection(enum e_token_type type, const char *file_name, \
t_executor *exec);

int	ft_wait_all_child(int pid);

#endif