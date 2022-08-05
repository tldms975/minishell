/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:20 by sielee            #+#    #+#             */
/*   Updated: 2022/08/06 01:51:45 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_bi_env(t_envp_list *env)
{
	t_envp_node	*ptr;

	ptr = env->head;
	//sort추가
	while (ptr)
	{
		printf("%s=%s\n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
	return (0);
}
int	main(int ac, char *av[], char *envp[])
{
	t_envp_list	env;
	int	ret;

	(void)av;
	(void)envp;
	ret = 0;
	if (ac > 1)
		ft_error("Wrong Argc\n");
	ft_init_env_list(&env, envp);
	ft_bi_env(&env);
	//ret = ft_minishell(&env);
	//ft_free
	return (ret);
}
