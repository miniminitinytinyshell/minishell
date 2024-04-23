/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:54:09 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/23 13:26:43 by hyeunkim         ###   ########.fr       */
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
		return (1);
	}
	else
	{
		ft_putendl_fd("env: undefined usage", STDERR_FILENO);
		return (126);
	}
}

int	builtin_env(char **args, t_envp *envp)
{
	int	i;

	i = 0;
	if (args[1])
		return (env_arg_error(args[1]));
	while (envp->data[i])
	{
		if (ft_strchr(envp->data[i], '='))
			ft_putendl_fd(envp->data[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
