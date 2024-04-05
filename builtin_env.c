/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:54:09 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/05 16:35:05 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	builtin_env(char **args, char **envp)
{
	int	idx;

	if (args[1])
	{
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putendl_fd("feature not supported", STDERR_FILENO);
		ft_putendl_fd("usage: env", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	idx = 0;
	while (envp[idx])
	{
		ft_putendl_fd(envp[idx], STDOUT_FILENO);
		idx++;
	}
	return (EXIT_SUCCESS);
}
