/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:45:00 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/18 14:55:53 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	pwd_option_error(char *option)
{
	ft_putstr_fd("mongshell: pwd: ", STDERR_FILENO);
	ft_putchar_fd(option[0], STDERR_FILENO);
	ft_putchar_fd(option[1], STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putendl_fd("pwd: usage: pwd", STDERR_FILENO);
	return (2);
}

static int	pwd_chk_option(char *option)
{
	int	len;

	len = ft_strlen(option);
	if (len < 2)
		return (0);
	if (len == 2 && option[1] == '-')
		return (0);
	return (1);
}

int	builtin_pwd(char **args, t_envp *envp)
{
	char	*pwd;
	int		flag;

	flag = 0;
	if (args[1] && args[1][0] == '-')
		flag = pwd_chk_option(args[1]);
	if (flag == 1)
		return (pwd_option_error(args[1]));
	pwd = envp->pwd;
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
