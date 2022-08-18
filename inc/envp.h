/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:27:29 by sielee            #+#    #+#             */
/*   Updated: 2022/08/18 19:11:41 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

typedef struct s_envp_node	t_envp_node;
typedef struct s_envp_list	t_envp_list;

struct s_envp_node
{
	char				*key;
	char				*value;
	struct s_envp_node	*next;
	struct s_envp_node	*prev;
};

struct s_envp_list
{
	struct s_envp_node	*head;
	struct s_envp_node	*tail;
	char				**vec;
	int					len;
};

void		ft_init_env_list(t_envp_list *env, char *envp[]);

void		ft_free_env_list(t_envp_list *env_list);
void		ft_free_env_vec(char *vec[]);

char		*ft_make_env_line(t_envp_node *node);
char		**ft_get_env_vector(t_envp_list *env);

t_envp_list	*ft_get_sorted_env(t_envp_list *env_list);

t_envp_node	*ft_get_env_node_ptr(t_envp_list *env, const char *key);
char		*ft_get_env_value_ptr(t_envp_list *env, const char *key);
void		ft_del_env_var(t_envp_list *env, char *key);
void		ft_add_env_var(t_envp_list *env, const char *key, \
			const char *value);
void		ft_mod_env_value(t_envp_list *env, const char *key, \
			const char *new_value);

#endif