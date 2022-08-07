/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:27:29 by sielee            #+#    #+#             */
/*   Updated: 2022/08/08 02:12:45 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

typedef struct s_envp_node	t_envp_node;
typedef struct s_envp_list	t_envp_list;

struct s_envp_node
{
	char	*key;
	char	*value;
	struct s_envp_node	*next;
};

struct s_envp_list
{
	struct s_envp_node	*head;
	struct s_envp_node	*tail;
	int					len;
};

void	ft_init_env_list(t_envp_list *env, char *envp[]);

char	*ft_make_env_line(t_envp_node *node);
char	**ft_get_env_vector(t_envp_list *env);

char	*ft_get_ptr_env_value(t_envp_list *env, const char *key, \
		t_envp_node *position);
void	ft_add_env_var(t_envp_list *env, const char *key, const char *value);
void	ft_mod_env_value(t_envp_list *env, const char *key, const char *value);

#endif