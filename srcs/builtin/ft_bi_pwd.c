/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:14:38 by sielee            #+#    #+#             */
/*   Updated: 2022/08/07 17:39:23 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_bi_pwd(t_pipe_line *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_perror("getcwd");
		ft_exit(EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	ft_free((void **) &pwd);
	return (EXIT_SUCCESS);
}
