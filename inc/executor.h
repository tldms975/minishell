/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:08:46 by sielee            #+#    #+#             */
/*   Updated: 2022/08/19 22:37:14 by sielee           ###   ########seoul.kr  */
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
typedef enum e_exe_in		t_exe_in;
typedef enum e_mybool		t_mybool;
typedef struct s_executor	t_executor;

enum e_exit
{
	EXIT_UNEXECUTABLE = 126,
	EXIT_NOTFOUND = 127,
	EXIT_OVER = 255
};

enum e_exe_in
{
	PARENT,
	CHILD,
	DO_NOT_EXE
};

enum e_read_write
{
	READ,
	WRITE
};

enum e_mybool
{
	FALSE,
	TRUE
};

struct s_executor
{
	pid_t		last_pid;
	pid_t		pid;
	int			fd_read;
	int			fd_write;
	int			l_pipe_fd[1];
	int			r_pipe_fd[2];
	int			heredoc_fd[2];
	int			heredoc_exit;
	t_mybool	is_heredoc;
	t_mybool	is_builtin;
	int			built_in_code;
	int			times;
	t_exe_in	in;
	t_envp_list	*env;
};

void	ft_print_errmsg_no_permission(char *file_name);

int		ft_check_builtin(t_pipe_node *cmd, t_executor *exec, int cnt_pipe);
int		ft_execute_built_in(t_pipe_node *cmd, int code);

int		ft_execute(t_pipe_list *pipe_list, t_envp_list *env_list);
void	ft_execute_cmd(t_arg_list *arg_list, t_envp_list *env);
void	ft_check_cmd_path(char *arg, char *cmd, char *msg);

void	ft_check_heredoc(t_limiter_q *lim_q, t_executor *exec, \
		t_envp_list *env_list, int *is_heredoc_in_pipe);

int		ft_check_valid_redir_files(t_arg_node *arg, t_redir_node *redir, \
		t_executor *exec);
int		ft_redirection(t_arg_node *arg, t_redir_node *redir, \
		t_executor *exec);

int		ft_get_child_exit_status(int status);
int		ft_wait_all_child(int last_pid);
void	ft_exe_in_child_process(t_pipe_node *cmd, t_executor *exec, \
		int cnt_pipe);
int		ft_exe_in_parent_process(t_pipe_node *cmd, t_executor *exec);

#endif