/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:26:15 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/03/28 14:44:19 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	builtin_echo(char **args, char **envp)
{
	int	idx;

	if (ft_strncmp(args[1], "-n", 3) == 0)
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

int	main(int argc, char **argv, char **envp)
{
	char	*args1[] = {"echo", "-n", "hello", NULL};
	char	*args2[] = {"echo", "hello", "-n", NULL};

	builtin_echo(args1, envp);
}