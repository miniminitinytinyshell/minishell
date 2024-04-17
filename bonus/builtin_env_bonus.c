/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:54:09 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/17 15:02:46 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"
#include "function_bonus.h"

static int	env_arg_error(char *option)
{
	if (option[0] == '-')
	{
		ft_putstr_fd("env: unrecognized option '", STDERR_FILENO);
		ft_putstr_fd(option, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		ft_putendl_fd("env : usage: env", STDERR_FILENO);
		return (125);
	}
	else
	{
		ft_putendl_fd("env: undefined usage", STDERR_FILENO);
		return (127);
	}
}

int	builtin_env(char **args, char **envp)
{
	int	idx;

	if (args[1])
		return (env_arg_error(args[1]));
	idx = 0;
	while (envp[idx])
	{
		ft_putendl_fd(envp[idx], STDOUT_FILENO);
		idx++;
	}
	return (EXIT_SUCCESS);
}
