/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:54:09 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/04 18:39:31 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	env_failure(void)
{
	ft_putendl_fd("minishell: env: illegal option or argument", STDERR_FILENO);
	ft_putendl_fd("usage: env", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	builtin_env(char **args, char **envp)
{
	int	idx;

	if (args[1])
		return (env_failure());
	idx = 0;
	while (envp[idx])
	{
		ft_putendl_fd(envp[idx], STDOUT_FILENO);
		idx++;
	}
	return (EXIT_SUCCESS);
}