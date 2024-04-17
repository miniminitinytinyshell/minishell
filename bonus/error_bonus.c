/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/17 15:02:46 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"
#include "function_bonus.h"

void	error_syscall(void)
{
	ft_putstr_fd("mongshell🐶: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	error_with_str(char *str, int flag)
{
	ft_putstr_fd("mongshell🐶: ", STDERR_FILENO);
	if (flag == CMD_NFOUND)
		ft_putstr_fd("command not found: ", STDERR_FILENO);
	else if (flag == IS_DIR)
		ft_putstr_fd("is a directory: ", STDERR_FILENO);
	else
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(str, STDERR_FILENO);
	if (flag == CMD_NFOUND)
		return (127);
	if (flag == IS_DIR)
		return (126);
	else
		return (1);
}

int	error_syntax(char *str, t_token **token, int flag)
{
	ft_putstr_fd("mongshell🐶: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	if (flag)
		ft_putchar_fd((char)flag, STDERR_FILENO);
	else
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	if (token)
		token_clear(token);
	return (0);
}

int	error_not_vaild(char *cmd, char *arg)
{
	ft_putstr_fd("mongshell🐶: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (1);
}
