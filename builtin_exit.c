/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:43:38 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/09 15:15:36 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	check_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '\n')
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			ft_putstr_fd("minishell: numeric argument required: ", STDERR_FILENO);
			ft_putendl_fd(arg, STDERR_FILENO);
			exit(255);
		}
		i++;
	}
	return (ft_atoi(arg));
}

int	builtin_exit(char **args)
{
	int	c;
	int	num;

	c = 0;
	while (args[c])
		c++;
	if (c == 1)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
	else if (c == 2)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		num = check_numeric(args[1]);
		if (num < 256)
			exit(num);
		else
			exit(num % 256);
	}
	else
		return (error_many_args(args[0]));
}
