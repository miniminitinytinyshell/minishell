/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:43:38 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/23 11:06:08 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	exit_many_args(void)
{
	ft_putstr_fd("mongshell: ", STDERR_FILENO);
	ft_putendl_fd("too many arguments", STDERR_FILENO);
	return (1);
}

int	exit_non_numeric(char *arg)
{
	ft_putstr_fd("mongshell: exit: ", STDERR_FILENO);
	ft_putstr_fd("numeric argument required: ", STDERR_FILENO);
	ft_putendl_fd(arg, STDERR_FILENO);
	exit(255);
}

int	check_longlong_range(char *arg)
{
	const char	*long_max = "9223372036854775807";
	const char	*long_min = "-9223372036854775808";
	size_t		len;

	while (*arg == ' ' || (8 < *arg && *arg < 14))
		arg++;
	len = ft_strlen(arg);
	if (arg[0] == '-')
	{
		if (len > ft_strlen(long_min))
			return (1);
		else if (ft_strncmp(long_min, arg, len + 1) < 0)
			return (1);
		else
			return (0);
	}
	else if (len > ft_strlen(long_max))
		return (1);
	else if (ft_strncmp(long_max, arg, len + 1) < 0)
		return (1);
	return (0);
}

int	check_numeric(char *arg)
{
	int	i;
	int	sign;

	if (check_longlong_range(arg))
		exit_non_numeric(arg);
	i = 1;
	sign = 1;
	if (arg[0] == '+' || arg[0] == '-')
	{
		if (arg[0] == '-')
			sign *= -1;
		i++;
	}
	while (arg[i] == ' ' || (8 < arg[i] && arg[i] < 14))
		i++;
	while (arg[i] && arg[i] != '\n')
	{
		if (ft_isdigit(arg[i]) == 0)
			exit_non_numeric(arg);
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
		return (exit_many_args());
}
