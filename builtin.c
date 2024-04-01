/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:26:15 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/01 22:49:14 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/libft/libft.h"
#include <stdio.h>

int	chk_echo_option(char *arg)
{
	const int	len = ft_strlen(arg);
	int			idx;

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

int	builtin_echo(char **args, char **envp)
{
	const int	flag = chk_echo_option(args[1]);
	int			idx;
	char		*arg1;

	if (flag == 1)
	{
		idx = 2;
		while (args[idx])
		{
			ft_putstr_fd(args[idx], STDOUT_FILENO);
			idx++;
		}
	}
	else
	{
		idx = 1;
		while (args[idx + 1])
		{
			ft_putstr_fd(args[idx], STDOUT_FILENO);
			ft_putchar_fd(' ', STDOUT_FILENO);
			idx++;
		}
		ft_putendl_fd(args[idx], STDOUT_FILENO);
	}
	exit(EXIT_SUCCESS);
}

// int	builtin_cd(char **argv, char **envp)
// {
// 	if (chdir(argv[0]) < 0)
// 		error_cd();
// 	exit(EXIT_SUCCESS);
// }

int	main(int argc, char **argv, char **envp)
{
	char	*args1[] = {"echo", "-nnnnnn", "hello", NULL};
	char	*args2[] = {"echo", "hello", "-n", NULL};

	builtin_echo(args1, envp);
}