/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:26:15 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/07 12:53:03 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	chk_echo_option(char *arg)
{
	int	len;
	int	idx;

	len = ft_strlen(arg);
	if (arg[0] != '-')
		return (0);
	idx = 1;
	while (idx < len)
	{
		if (arg[idx] != 'n')
			return (0);
		idx++;
	}
	return (1);
}

static void	echo_option(char **args)
{
	int	idx;

	idx = 2;
	if (!args[idx])
		ft_putendl_fd("", STDOUT_FILENO);
	while (args[idx])
	{
		ft_putstr_fd(args[idx], STDOUT_FILENO);
		if (args[idx + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		idx++;
	}
}

static void	echo_no_option(char **args)
{
	int	idx;

	idx = 1;
	if (!args[idx])
		ft_putendl_fd("", STDOUT_FILENO);
	while (args[idx + 1])
	{
		ft_putstr_fd(args[idx], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		idx++;
	}
	ft_putendl_fd(args[idx], STDOUT_FILENO);
}

int	builtin_echo(char **args)
{
	int	flag;

	if (!args[1])
	{
		ft_putendl_fd("", STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	flag = chk_echo_option(args[1]);
	if (flag == 1)
		echo_option(args);
	else
		echo_no_option(args);
	return (EXIT_SUCCESS);
}
