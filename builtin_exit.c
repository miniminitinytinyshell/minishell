/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:43:38 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/17 14:18:45 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	error_many_args(void)
{
	ft_putstr_fd("mongshell🐶: ", STDERR_FILENO);
	ft_putendl_fd("too many arguments", STDERR_FILENO);
	return (1);
}

int	check_numeric(char *arg)
{
	int	i;
	int	sign;

	i = 1;
	sign = 1;
	if (arg[0] == '+' || arg[0] == '-')
	{
		if (arg[0] == '-')
			sign *= -1;
		i++;
	}
	while (arg[i] && arg[i] != '\n')
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			ft_putstr_fd("mongshell🐶: exit: ", STDERR_FILENO);
			ft_putstr_fd("numeric argument required: ", STDERR_FILENO);
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
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else if (c == 2)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		num = check_numeric(args[1]);
		if (num < 256)
			exit(num);
		else
			exit(num % 256);
	}
	else
		return (error_many_args());
}
